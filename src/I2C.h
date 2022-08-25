/**
 * @file I2C.h
 * @author USST WangYJ (2035060326)
 * @brief I2C
 * @version 1.0
 * @date 2022-08-23
 * 
 * 
 */

#ifndef __I2C_H__
#define __I2C_H__

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveAck(void);


#endif
