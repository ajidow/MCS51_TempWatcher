/**
 * @file Delay.c
 * @author WangYJ
 * @brief A set of Delay function. Based on occupying CPU. Including delay xms,1us,100us,500us,70us. Using timer are recommened.
 * @freq: 11.0592MHz
 * @version 1.0
 * @date 2020-04-18
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <intrins.h>

void Delayms(unsigned int x)
{
	while (x--)
	{
		unsigned char i, j;
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j)
				;
		} while (--i);
	}
}

void Delay1us()
{
	_nop_();
	_nop_();
	_nop_();
}

void Delay100us()
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j)
			;
	} while (--i);
}

void Delay500us()
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j)
			;
	} while (--i);
}

void Delay70us()
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 1;
	j = 189;
	do
	{
		while (--j)
			;
	} while (--i);
}
