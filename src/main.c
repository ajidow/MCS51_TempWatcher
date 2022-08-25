/**
 * @file main.c
 * @author USST WangYJ (2035060326)
 * @brief
 * @version 0.1
 * @date 2022-08-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <REGX52.H>
#include "Driver_AT24C02.h"
#include "Driver_LCD1602.h"
#include "Driver_DS18B20.h"
#include "Delay.h"
#include "GetKey.h"
#include "Timer.h"
#include "UART.h"

#define MAXTEMP 125
#define MINTEMP -55

float T, TempShow;
char TempLowThreshold, TempHighThreshold;
unsigned char KeyNum;
unsigned char TemperatureCache[60];
unsigned char TempCacheTop = 0;
unsigned char IndexUpperBoundary;

/**
 * @brief Initialize. Call it at the beginning of main().
 *
 */
void Init()
{
	LCD_Init();
	LCD_ShowString(1, 1, "Loading...");

	// Getting temperature threshold from AT24C02
	TempHighThreshold = AT24C02_ReadByte(0);
	TempLowThreshold = AT24C02_ReadByte(1);

	// Recover Thresholds if they are invalid.
	if (TempHighThreshold > 125 || TempLowThreshold < -55 || TempLowThreshold >= TempHighThreshold)
	{
		TempHighThreshold = 20;
		TempLowThreshold = 15;
		AT24C02_WriteByte(0, TempHighThreshold);
		Delayms(5);
		AT24C02_WriteByte(1, TempLowThreshold);
		Delayms(5);
	}

	// UI based on LCD1605
	LCD_ShowString(2, 1, "H:");
	LCD_ShowString(2, 8, "L:");
	LCD_ShowSignedNum(2, 3, TempHighThreshold, 3);
	LCD_ShowSignedNum(2, 11, TempLowThreshold, 3);

	// Convert Temperature is necessary here. Or the data read may be wrong because of time sequence error.
	DS18B20_ConvertT();
	Delayms(1000);

	Timer0Init();
	UART_Init();
	LCD_ShowString(2, 1, "                ");
}

/**
 * @brief Show the temperature on LCD1602.
 *
 */
void ShowTemp()
{
	DS18B20_ConvertT();
	T = DS18B20_ReadT();
	if (T < 0)
	{
		LCD_ShowChar(1, 6, '-');
		TempShow = -T;
	}
	else
	{
		LCD_ShowChar(1, 6, ' ');
		TempShow = T;
	}
	LCD_ShowNum(1, 7, TempShow, 3);
	LCD_ShowChar(1, 10, '.');
	LCD_ShowNum(1, 11, (unsigned long)(TempShow * 100) % 100, 2);
}

/**
 * @brief Modify the temperature threshold when certain keys(1,2,3 and 4) are pressed.
 *
 */
void ModifyTemp()
{
	if (KeyNum > 0 && KeyNum < 10)
	{
		if (KeyNum == 1)
		{
			TempHighThreshold++;
			P2_4 = 0;
			if (TempHighThreshold > MAXTEMP)
			{
				TempHighThreshold = MAXTEMP;
			}
		}
		if (KeyNum == 2)
		{
			TempHighThreshold--;
			if (TempHighThreshold <= TempLowThreshold)
			{
				TempHighThreshold++;
			}
		}
		if (KeyNum == 3)
		{
			TempLowThreshold++;
			if (TempLowThreshold >= TempHighThreshold)
			{
				TempLowThreshold--;
			}
		}
		if (KeyNum == 4)
		{
			TempLowThreshold--;
			if (TempLowThreshold < MINTEMP)
			{
				TempLowThreshold = MINTEMP;
			}
		}
		LCD_ShowString(2, 1, "TH:");
		LCD_ShowString(2, 9, "TL:");
		LCD_ShowSignedNum(2, 4, TempHighThreshold, 3);
		LCD_ShowSignedNum(2, 12, TempLowThreshold, 3);
		AT24C02_WriteByte(0, TempHighThreshold);
		Delayms(5);
		AT24C02_WriteByte(1, TempLowThreshold);
		Delayms(65);
		LCD_ShowString(2, 1, "                ");
	}
}

/**
 * @brief Check if the Temperature is acceptable.
 *
 */
void ThresholdCheck()
{
	if (T > TempHighThreshold)
	{
		LCD_ShowString(2, 1, "Too Hot");
	}
	else if (T < TempLowThreshold)
	{
		LCD_ShowString(2, 1, "Too Cold");
	}
	else if (T >= TempLowThreshold)
	{
		LCD_ShowString(2, 1, "        ");
	}
	else
	{
		LCD_ShowString(2, 1, "                ");
	}
}

/**
 * @brief Save the Temperature data in the buffer into AT24C02 when key 16 is pressed. And Upload it through UART to PC when key 12 is pressed/
 *
 */
void SaveAndUpload()
{
	unsigned char cnt;
	if (KeyNum == 16)
	{
		IndexUpperBoundary = TempCacheTop;
		LCD_Clear();
		Delayms(5);
		LCD_ShowString(1, 1, "Saving...");
		for (cnt = 0; cnt < IndexUpperBoundary; ++cnt)
		{
			AT24C02_WriteByte(cnt + 3, TemperatureCache[cnt]);
			Delayms(5);
		}
		LCD_Clear();
		LCD_ShowString(1, 1, "Temp:");
	}
	else if (KeyNum == 12)
	{
		LCD_Clear();
		Delayms(5);
		LCD_ShowString(1, 1, "Uploading...");
		for (cnt = 0; cnt < IndexUpperBoundary; ++cnt)
		{
			unsigned char temp = AT24C02_ReadByte(cnt + 3);
			Delayms(5);
			UART_SendByte(temp);
			Delayms(1);
		}
		LCD_Clear();
		LCD_ShowString(1, 1, "Temp:");
	}
}

void main()
{
	Init();
	LCD_ShowString(1, 1, "Temp:");

	while (1)
	{
		ShowTemp();

		KeyNum = Key();
		ModifyTemp();

		ThresholdCheck();
		SaveAndUpload();
	}
}

void T0_Int() interrupt 1
{
	static unsigned int T0Count, saveCount;
	TL0 = 0x66;
	TH0 = 0xFC;
	T0Count++;
	saveCount++;
	if (T0Count >= 20)
	{
		T0Count = 0;
		Key_Loop();
	}
	if (saveCount >= 1000)
	{
		saveCount = 0;
		if (TempCacheTop >= 60)
			TempCacheTop = 0;
		TemperatureCache[TempCacheTop++] = T;
	}
}
