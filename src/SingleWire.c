#include <regx52.h>
#include "Delay.h"

sbit SingleWire_DQ = P3 ^ 7;

/**
 * @brief
 * @param  无
 * @retval slave response，0:response，1:not response
 */
unsigned char SingleWire_Init(void)
{
	unsigned char AckBit;
	EA = 0;
	SingleWire_DQ = 1;
	SingleWire_DQ = 0;
	Delay500us();

	SingleWire_DQ = 1;
	Delay70us();

	AckBit = SingleWire_DQ;
	Delay500us();
	
	EA = 1;
	return AckBit;
}

/**
 * @brief  SW send bit
 * @param  Bit The bit data to send
 * @retval void
 */
void SingleWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	EA = 0;
	SingleWire_DQ = 0;
	i = 4;
	while (--i)
		; // Delay 10us
	SingleWire_DQ = Bit;
	i = 24;
	while (--i)
		; // Delay 50us
	SingleWire_DQ = 1;
	EA = 1;
}

/**
 * @brief  SW get bit
 * @param  NA
 * @retval The got data.
 */
unsigned char SingleWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	EA = 0;
	SingleWire_DQ = 0;
	i = 2;
	while (--i)
		; // Delay 5us
	SingleWire_DQ = 1;
	i = 2;
	while (--i)
		; // Delay 5us
	Bit = SingleWire_DQ;
	i = 24;
	while (--i)
		; // Delay 50us
	EA = 1;
	return Bit;
}

/**
 * @brief  SW send byte
 * @param  Byte Byte 2b sent
 * @retval void
 */
void SingleWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		SingleWire_SendBit(Byte & (0x01 << i));
	}
}

/**
 * @brief  SW reveive byte
 * @param  NA
 * @retval byte received
 */
unsigned char SingleWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte = 0x00;
	for (i = 0; i < 8; i++)
	{
		if (SingleWire_ReceiveBit())
		{
			Byte |= (0x01 << i);
		}
	}
	return Byte;
}
