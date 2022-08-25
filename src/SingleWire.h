#ifndef __SINGLEWIRE_H__
#define __SINGLEWIRE_H__

unsigned char SingleWire_Init(void);
void SingleWire_SendBit(unsigned char Bit);
unsigned char SingleWire_ReceiveBit(void);
void SingleWire_SendByte(unsigned char Byte);
unsigned char SingleWire_ReceiveByte(void);

#endif
