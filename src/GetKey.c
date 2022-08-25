/**
 * @file GetKey.c
 * @author USST WangYJ(2035060326)
 * @brief The modified version of GetKey v1.0 . Added the function Key_GetState and added Key_loop
 * @version 1.1
 * @date 2022-08-23
 *
 */

#include <REGX52.H>
#include "Delay.h"

unsigned char Key_KeyNumber;

/**
 * @brief  Get key number
 * @param  NA
 * @retval unsigned char, Referring the key pressed. Ranges from 1 to 4 with a special code 0 means no key was triggered.
 */
unsigned char Key(void)
{
	unsigned char Temp = 0;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}

/**
 * @brief  Get the state of key.
 * @warning Viberating has NOT been smoothed yet.
 * @param  NA
 * @retval unsigned char, Referring the key pressed. Ranges from 1 to 4 with a special code 0 means no key was triggered.
 */
unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;

	if (P3_1 == 0)
	{
		KeyNumber = 1;
	}
	if (P3_0 == 0)
	{
		KeyNumber = 2;
	}
	if (P3_2 == 0)
	{
		KeyNumber = 3;
	}
	if (P3_3 == 0)
	{
		KeyNumber = 4;
	}
	P1 = 0xFF;
	P1_0 = 0;
	if (P1_4 == 0)
	{
		KeyNumber = 16;
	}
	else if (P1_5 == 0)
	{
		KeyNumber = 12;
	}
	return KeyNumber;
}

/**
 * @brief  This is a function used in interreption.
 * @param  NA
 * @retval void
 */
void Key_Loop(void)
{
	static unsigned char NowState, LastState;
	LastState = NowState;
	NowState = Key_GetState();
	if (LastState == 1 && NowState == 0)
	{
		Key_KeyNumber = 1;
	}
	if (LastState == 2 && NowState == 0)
	{
		Key_KeyNumber = 2;
	}
	if (LastState == 3 && NowState == 0)
	{
		Key_KeyNumber = 3;
	}
	if (LastState == 4 && NowState == 0)
	{
		Key_KeyNumber = 4;
	}
	if (LastState == 16 && NowState == 0)
	{
		Key_KeyNumber = 16;
	}
	if(LastState == 12 && NowState == 0)
	{
		Key_KeyNumber = 12;
	}
}
