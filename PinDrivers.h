/*
 * IoDrivers.h
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */

#ifndef PINDRIVERS_H_
#define PINDRIVERS_H_

#include <avr/io.h>
#include "IoLines.h"
#include "macros.h"

void LcdWrite(void);
void LcdDataEn(void);
void LcdInstrEn(void);
void SPI_Tx(uint8_t data);
uint8_t SPI_Rx(void);
uint8_t isCMRunning();

#endif /* PINDRIVERS_H_ */
