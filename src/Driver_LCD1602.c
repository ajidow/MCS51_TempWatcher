/**
 * @file Driver_LCD1602.c
 * @author USST WangYJ (2035060326)
 * @brief The driver of LCD1602
 * @version 1.0
 * @date 2022-08-23
 *
 *
 */

#include <regx52.h>
#include <intrins.h>
#include "Delay.h"

sbit LCD_RS = P2 ^ 6;
sbit LCD_RW = P2 ^ 5;
sbit LCD_EN = P2 ^ 7;
#define LCD_DP P0

/**
 * @brief  LCD1602 Write command
 * @param  Command The command to be written
 * @retval void
 */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DP = Command;
	LCD_EN = 1;
	Delayms(1);
	LCD_EN = 0;
	Delayms(1);
}

/**
 * @brief  LCD1602 Write data
 * @param  Data The data to be written
 * @retval void
 */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DP = Data;
	LCD_EN = 1;
	Delayms(1);
	LCD_EN = 0;
	Delayms(1);
}

/**
 * @brief  LCD1602 set cursor pos
 * @param  Line row position. Ranges from 1 to 2
 * @param  Column col position. Ranges from 1 to 16
 * @retval void
 */
void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if (Line == 1)
	{
		LCD_WriteCommand(0x80 | (Column - 1));
	}
	else if (Line == 2)
	{
		LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
	}
}

/**
 * @brief  LCD1602 init settings
 * @param  NA
 * @retval void
 */
void LCD_Init()
{
	LCD_WriteCommand(0x38); // 8 bit. 2 lines. 5*7 matrix.
	LCD_WriteCommand(0x0c); // display on. cursor off. flash off.
	LCD_WriteCommand(0x06); // cursot move right.
	LCD_WriteCommand(0x01); // clear.
}

/**
 * @brief  Show certain character
 * @param  Line row position. Ranges from 1 to 2
 * @param  Column col position. Ranges from 1 to 16
 * @param  Char Character to be shown
 * @retval void
 */
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

/**
 * @brief  Show certain string
 * @param  Line row position. Ranges from 1 to 2
 * @param  Column col position. Ranges from 1 to 16
 * @param  string String to be shown
 * @retval void
 */
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = 0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
 * @brief  Carmichael Numbers for LCD_Pow. It's just a roast->快速幂 IS POWER!!!!!!!!!!!!! 某noi教练如是说
 * @param  X truth
 * @param  Y power
 * @retval An integer, presented as X^Y.
 */
int LCD_Pow(int X, int Y)
{
	int ret = 1;
	if (X == 0)
		ret = 0;
	else if (Y == 0 && X != 1)
	{
		ret = 1;
	}
	else
	{
		while (Y != 0)
		{
			if (Y & 1)
				ret *= X;
			X *= X;
			Y >>= 1;
		}
	}
	return ret;
}

/**
 * @brief  Show certain number(unsigned)
 * @param  Line row position. Ranges from 1 to 2
 * @param  Column col position. Ranges from 1 to 16
 * @param  Number Number(Integer) to be shown. Ranges from 0 to 65535
 * @param  Length length of number.Ranges form 1 to 5
 * @retval void
 */
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief  Show certain number(signed)
 * @param  Line row position. Ranges from 1 to 2
 * @param  Column col position. Ranges from 1 to 16
 * @param  Number Number(Integer) to be shown. Ranges from -32768 to 32767
 * @param  Length length of number.Ranges form 1 to 5
 * @retval void
 */
void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line, Column);
	if (Number >= 0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number1 / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief  Show certain number(Hex)
 * @param  Line row position. Ranges from 1 to 2
 * @param  Column col position. Ranges from 1 to 16
 * @param  Number Number(Hex) to be shown. Ranges from 0 to 0xFFFF
 * @param  Length length of number. Ranges form 1 to 4
 * @retval void
 */
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i, SingleNumber;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		SingleNumber = Number / LCD_Pow(16, i - 1) % 16;
		if (SingleNumber < 10)
		{
			LCD_WriteData(SingleNumber + '0');
		}
		else
		{
			LCD_WriteData(SingleNumber - 10 + 'A');
		}
	}
}

/**
 * @brief  Show certain number(Bineary)
 *@param  Line row position. Ranges from 1 to 2
 * @param  Column col position. Ranges from 1 to 16
 * @param  Number Number to be shown. Ranges from 0 to 1111 1111 1111 1111b
 * @param  Length length of number. Ranges form 1 to 16
 * @retval void
 */
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(2, i - 1) % 2 + '0');
	}
}

/**
 * @brief Clear LCD
 */
void LCD_Clear()
{
	LCD_ShowString(1,1,"                ");
	LCD_ShowString(2,1,"                ");
}