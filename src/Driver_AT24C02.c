/**
 * @file Driver_AT24C02.c
 * @author USST WangYJ (2035060326)
 * @brief Driver of AT24C02. For storing data.
 * @version 0.2
 * @date 2022-08-23
 * 
 * 
 */

#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS		0xA0

/**
  * @brief  AT24C02 write byte
  * @param  Address Address of the data
  * @param  Data The data
  * @retval void
  */
void AT24C02_WriteByte(unsigned char Address,unsigned char Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Address);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

/**
  * @brief  AT24C02 Read byte
  * @param  Address Address of the data
  * @retval unsighed char referring data read.
  */
unsigned char AT24C02_ReadByte(unsigned char Address)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Address);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}
