/*
 * ChipInit.c
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */

#include <avr/io.h>
#include "ChipInit.h"

/***********************************************************
*		IO Configuration
***********************************************************/

void IO_config(void)
{

 DDRB  = BIT(USB_POWER_GATE)|BIT(USB_DATA_nGATE);
 PORTB = BIT(USB_POWER_GATE);

 DDRC  = BIT(LCD_E)|BIT(LCD_RnW)|BIT(LCD_RS)|BIT(nPOWER_OFF); // Compute modules
 PORTC = BIT(nPOWER_OFF);

 DDRD  = 0b11111111; // LCD data lines
 PORTD = 0b00000000;

}




/***********************************************************
*		SPI Configuration
***********************************************************/
void SPI_config(void)
{
 SPCR = BIT(SPE)|BIT(SPIE);
 SPSR = 0X00;
 uint8_t dummy = SPSR;
 dummy = SPDR;
}


/**********************************************************
 *      Pin change configuration
 *********************************************************/
void PCINT_config(void)
{
	PCMSK0 = 0b11100000;
	PCMSK1 = 0b10000000;
}


void counter0_init(uint8_t prescaler)
{
 TCNT0=0x40;
 TCCR0A = prescaler; // 1 -> 5
 TIMSK0 = BIT(TOIE0);  // enable overflow interrupt
}


/***********************************************************
*				Configuring the chip
***********************************************************/
void config_chip(void)
{
 CLI(); //disable all interrupts*/
 IO_config();
 SPI_config();
 counter0_init(5);

 MCUCR = 0x00;
 TIMSK1 = 0x00;
 TIMSK2 = 0x00;
 SEI(); /*re-enable interrupts*/
}
