/*
 * IoLines.h
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */

#ifndef IOLINES_H_
#define IOLINES_H_

//#include "macros.h"


/*** PORTB ***/
//#define BUTTON_PUSHED		7
//#define LCD_RS		6    //Xmega: 2
#define SPI_SCK		5    //Xmega: 1
#define SPI_MISO		4    //Xmega: 0
#define SPI_MOSI 	3    //Xmega: 6
#define SPI_nCS 	2    //Xmega: 5
#define USB_DATA_nGATE 	1    //Xmega: 7
#define USB_POWER_GATE  	0    //Xmega: 4

/*** PORTC ***/
#define LCD_E	0
#define LCD_RnW		1
#define LCD_RS		2
#define nPOWER_BUTTON	3
#define PEDAL_OUTPUT_nEN	4  // also use to detect CM powered-off state when MCU is in power-off mode.
#define nPOWER_OFF		5
/*** PORTD ***/
// LCD data lines




#endif /* IOLINES_H_ */
