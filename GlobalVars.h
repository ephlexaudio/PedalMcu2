/*
 * GlobalVars.h
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */

#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

#include <ctype.h>
#include <stdint.h>

#define SPI_TX_BUFFER_SIZE  50
#define SPI_RX_BUFFER_SIZE  50


/****************** UI LCD and Buttons ***********************/
char debugString[20];

char displayLine[20];
uint8_t displayLineIndex;
uint8_t displayLineCharIndex;


#endif /* GLOBALVARS_H_ */
