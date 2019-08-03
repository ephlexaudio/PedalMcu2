/*
 * UserInterface.h
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "PinDrivers.h"
#include "IoLines.h"
#include "macros.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define LCD_LINE1_ADDR 0x00
#define LCD_LINE2_ADDR 0x40
#define LCD_LINE3_ADDR 0x14
#define LCD_LINE4_ADDR 0x54
#define SET_DDRAM_ADDRESS 0x80

void LCD_data(uint8_t data);
void LCD_instr(uint8_t data);
void LCD_init(void);
void Display(uint8_t lineIndex, char *line);

uint8_t isPowerOffButtonPushed(void);
#endif /* USERINTERFACE_H_ */
