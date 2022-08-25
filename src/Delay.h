/**
 * @file Delay.h
 * @author WangYJ
 * @brief A set of Delay function. Based on occupying CPU. Including delay xms,1us,100us. Using timer are recommened.
 * @freq: 11.0592MHz
 * @version 1.0
 * @date 2020-04-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __DELAY_H__
#define __DELAY_H__

void Delayms(unsigned int x);
void Delayus();
void Delay100us();
void Delay500us();
void Delay70us();
#endif
