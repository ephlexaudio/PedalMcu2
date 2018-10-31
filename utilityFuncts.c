/*
 * utilityFuncts.c
 *
 *  Created on: Mar 5, 2016
 *      Author: mike
 */

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "GlobalVars.h"
#include "macros.h"
#include "utilityFuncts.h"


void delay(unsigned long delay)
{
 unsigned long i;

 for (i = 0; i < delay; i++)
 {
  NOP();
 }
}

void clearBuffer(char *buffer, int length)
{
	uint16_t index;

	for(index = 0; index < length; index++)
	{
		buffer[index] = 0;
	}
}





