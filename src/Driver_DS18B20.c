/**
 * @file Driver_DS18B20.c
 * @author WangYJ
 * @brief Driver for DS18B20. DS18B20 is a thermometer.
 * @version 1.0
 * @date 2021-05-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <regx52.h>
#include "SingleWire.h"

// DS18B20 commands
#define DS18B20_SKIP_ROM 0xCC
#define DS18B20_CONVERT_T 0x44
#define DS18B20_READ_SCRATCHPAD 0xBE

/**
 * @brief  DS18B20 Start converting temperature
 * @param  na
 * @retval void
 */
void DS18B20_ConvertT(void)
{
	SingleWire_Init();
	SingleWire_SendByte(DS18B20_SKIP_ROM);
	SingleWire_SendByte(DS18B20_CONVERT_T);
}

/**
 * @brief  DS18B20 Read temperature
 * @param  na
 * @retval Float. Referring temperature.
 */
float DS18B20_ReadT(void)
{
	unsigned char TLSB, TMSB;
	int Temp;
	float T;

	SingleWire_Init();
	SingleWire_SendByte(DS18B20_SKIP_ROM);
	SingleWire_SendByte(DS18B20_READ_SCRATCHPAD);

	TLSB = SingleWire_ReceiveByte();
	TMSB = SingleWire_ReceiveByte();

	Temp = (TMSB << 8) | TLSB;
	T = Temp / 16.0;
	
	return T;
}
