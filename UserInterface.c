/*
 * UserInterface.c
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */
#include "UserInterface.h"
#include "utilityFuncts.h"
#include "GlobalVars.h"
#include <avr/io.h>



/***********************************************************
 *			Writing data uint8_ts to LCD Display
 ***********************************************************/
void LCD_data(uint8_t data)
{
	{
		PORTD = data;
		LcdDataEn();
		LcdWrite();
		delay(10);  //60
		PORTD = 0x00;
	}
}

/***********************************************************
 *			Writing instructions to LCD Display
 ***********************************************************/
void LCD_instr(uint8_t data)
{
	PORTD = data;
	LcdInstrEn();
	LcdWrite();
	delay(50);  //300
	PORTD = 0x00;
}


/***********************************************************
 *					Initializing LCD Display
 ***********************************************************/

void LCD_init(void)
{
	delay(2000); //1000
	LCD_instr(0x030);
	delay(666); //333
	LCD_instr(0x030);
	delay(200); //100
	LCD_instr(0x030);
	delay(200); //100
	LCD_instr(0b00111000);
	LCD_instr(0x010);
	LCD_instr(0x001);
	LCD_instr(0b00000110);
	LCD_instr(0b00001100);
}


/*uint8_t internalDisplayLineIndex = 0;
uint8_t receiveState = 0;*/

ISR(SPI_STC_vect)
{

	char receivedChar;
	static uint8_t receiveState;
	static uint8_t internalDisplayLineIndex;
	receivedChar = SPDR;
	switch(receiveState)
	{
		case 0: // start recieve: first recieved character is LCD line number
			internalDisplayLineIndex = receivedChar;
			displayLineCharIndex = 0;
			receiveState = 1;
			break;
		case 1: // recieved character is part of string

			if(receivedChar != 0)
			{
				displayLine[displayLineCharIndex++] = receivedChar;
			}
			else // end of transmission
			{
				receiveState = 0;

				for(int i = displayLineCharIndex; i < 20; i++)
				{
					displayLine[i] = ' ';
				}

				displayLineIndex = internalDisplayLineIndex;
				displayLineCharIndex = 0;
			}

			break;
		default:;
	}

}
/***********************************************************
 *		Writing strings to LCD Display
 ***********************************************************/

void Display(uint8_t lineIndex, char *line)
{
	uint8_t n=0;

	switch(lineIndex)
	{
		case 1:
			LCD_instr(0x01);
			LCD_instr(0b00000110);
			break;
		case 2:
			LCD_instr(SET_DDRAM_ADDRESS + LCD_LINE2_ADDR);
			break;
		case 3:
			LCD_instr(SET_DDRAM_ADDRESS + LCD_LINE3_ADDR);
			break;
		case 4:
			LCD_instr(SET_DDRAM_ADDRESS + LCD_LINE4_ADDR);
			break;
		default:;
	}

	while((*(line + n) != '\0') && (n < 20))
	{
		LCD_data((uint8_t)(*(line + n)));
		n++;
	}
}


uint8_t isPowerOffButtonPushed()
{
	uint8_t status = 0;

	if((PINC & BIT(nPOWER_BUTTON)) == 0)
	{
		status = 1;
	}

	return status;
}
