/*
 * IoDrivers.c
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */

#include "PinDrivers.h"
#include "GlobalVars.h"
#include <avr/io.h>

extern void delay(unsigned long delay);

void LcdWrite(void)
{
	PORTC |= BIT(LCD_E);
	delay(200);
	PORTC &= ~BIT(LCD_E);
}

void LcdDataEn(void)	//Set R/S pin high
{
	PORTC |= BIT(LCD_RS);
}

void LcdInstrEn(void)	  //Set R/S pin low
{
	PORTC &= ~BIT(LCD_RS);
}



/*****************************************************/
/*****************************************************/
/*****************************************************/


void SPI_Tx(uint8_t data)
{
 char dummy;
 SPDR = data;
 while(!(SPSR & BIT(SPIF))){} //Wait for Tx to complete
 dummy = SPDR; //access SPDR to clear SPIF bit
}

uint8_t SPI_Rx(void)
{
 uint8_t data;
 SPDR = 0x00;
 while(!(SPSR & BIT(SPIF))){} //Wait for Rx to complete
 data = SPDR;
 return data;
}

uint8_t isCMRunning()
{
	uint8_t status = 0;

	if((PINC & BIT(PEDAL_OUTPUT_nEN)) != 0)
	{
		status = 1;
	}

	return status;

}
