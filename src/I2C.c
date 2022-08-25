/**
 * @file I2C.c
 * @author USST WangYJ (2035060326)
 * @brief I2C
 * @version 1.0
 * @date 2022-08-23
 *
 *
 */

#include <regx52.h>

sbit I2C_SCL = P2 ^ 1;
sbit I2C_SDA = P2 ^ 0;

/**
 * @brief Start I2C communication. Call it before any operations through I2C.
 * @retval void
 */
void I2C_Start(void)
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}

/**
 * @brief Stop I2C communication. Call it after I2C is no more needed.
 * @retval void
 */
void I2C_Stop(void)
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}

/**
 * @brief  I2C Send a Byte
 * @param  Byte The byte to be sent
 * @retval void
 */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		I2C_SDA = Byte & (0x80 >> i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

/**
 * @brief  I2C Receive a Byte
 * @param  NA
 * @retval The Byte received
 */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i, Byte = 0x00;
	I2C_SDA = 1;
	for (i = 0; i < 8; i++)
	{
		I2C_SCL = 1;
		if (I2C_SDA)
		{
			Byte |= (0x80 >> i);
		}
		I2C_SCL = 0;
	}
	return Byte;
}

/**
 * @brief  I2C Send ack
 * @param  AckBit 0:ack  1:not ack
 * @retval void
 */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

/**
 * @brief  I2C Receive ack
 * @param  NA
 * @retval Ack bit received. 0:ack，1:not ack
 */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}
