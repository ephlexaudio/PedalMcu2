/*
 * main.c
 *
 *  Created on: Jul 20, 2017
 *      Author: buildrooteclipse
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilityFuncts.h"
#include "PinDrivers.h"
#include "ChipInit.h"
#include "UserInterface.h"
#include "GlobalVars.h"

void main()
{
	uint8_t dummy = 0;
	long powerOffCount = 0;
	displayLineIndex = 0;
	displayLineCharIndex = 0;

	config_chip();
	while(1)
	{
		if(isPowerOffButtonPushed() != 0)
		{
			delay(100);
			if(isPowerOffButtonPushed() != 0) break;
		}
	}

	LCD_init();
	Display(2,"   Ephlex Audio    ");
	Display(3,"      FLX-1        ");


	long cmDetectCount = 0;

	while(1)
	{
		if(isCMRunning() == 0) // Compute module is still powering on.
		{
			cmDetectCount++;
			if(cmDetectCount > 1000000)
			{
				Display(1,"Compute Module  ");
				Display(2,"missing         ");
				break;
			}
		}
		else	// Compute module is up and running;
		{
			cmDetectCount = 0;
			if(isPowerOffButtonPushed() != 0)
			{
				{
					powerOffCount++;
					if(isCMRunning() == 0)
					{
						Display(1,"powered off      ");
						Display(2,"release button   ");
						break;
					}
				}
			}
			else
			{
				powerOffCount = 0;
			}
		}

		if(displayLineIndex > 0)
		{
			Display(displayLineIndex, displayLine);
			displayLineIndex = 0;
		}
	}

	 while(isPowerOffButtonPushed() != 0); // wait until power button is released
	 delay(50000);

	 /*******************************************************************
	  *
	  * !!!!!!!!!!!! DON'T UNCOMMENT THE SHUTOFF LINE          	!!!!!!!!!
	  * !!!!!!!!!!!! UNTIL EVERYTHING ELSE IS ABSOLUTELY       	!!!!!!!!!
	  * !!!!!!!!!!!! READY 										!!!!!!!!
	  *
	  * !!!!!!!!!!!! REMEMBER TO JUMPER THE POWER-OFF LINE TO 	!!!!!!!!
	  * !!!!!!!!!!!! 3.3V LINE TO PREVENT SHUTOFF WHEN  		!!!!!!!!
	  * !!!!!!!!!!!! PROGRAMMING MCU					 		!!!!!!!!
	  ******************************************************************/
	 DDRC &= ~BIT(nPOWER_OFF);  // SHUTOFF LINE
	 while(1);
}
