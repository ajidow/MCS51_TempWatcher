#include <REGX52.H>

/**
 * @brief  9600bps
 */
void UART_Init()
{
	SCON = 0x40;
	PCON |= 0x80;
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TL1 = 0xFA;
	TH1 = 0xFA;
	ET1 = 0;
	TR1 = 1;
}

/**
 * @brief  Send Byte
 * @param  Byte Byte
 * @retval void
 */
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while (TI == 0)
		;
	TI = 0;
}
