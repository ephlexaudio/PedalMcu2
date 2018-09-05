/*
 * UserInterface.c
 *
 *  Created on: Jan 14, 2016
 *      Author: mike
 */
#include "UserInterface.h"
//#include "ComputeModuleFuncts.h"
#include "utilityFuncts.h"
#include "GlobalVars.h"
#include <avr/io.h>
//#include <avr/iom168.h>
#define NULL 0
//#define MCU_SHARED_MEMORY_SECTION_ADDRESS 0
//#define CM0_SHARED_MEMORY_SECTION_ADDRESS 4096
#define SHARED_MEMORY_SECTION_SIZE 4096
#define MCU_SHARED_MEMORY_SECTION_INDEX 0
#define CM0_SHARED_MEMORY_SECTION_INDEX 1

typedef uint8_t uint8_t;
extern void clearBuffer(char *buffer, int length);
//extern void clearBuffer(char *buffer, int length);

#define dbgUi 0
extern const char *testJson;

/*static void breakButtonUi(char *buffer1, char *buffer2, char *buffer3, char *buffer4)
{

	char tempBuffer[4][20];
	clearBuffer(tempBuffer[0],20);
	clearBuffer(tempBuffer[1],20);
	clearBuffer(tempBuffer[2],20);
	clearBuffer(tempBuffer[3],20);

	strncpy(tempBuffer[0],buffer1,20);
	strncpy(tempBuffer[1],buffer2,20);
	strncpy(tempBuffer[2],buffer3,20);
	strncpy(tempBuffer[3],buffer4,20);

	CLI();

	clearBuffer(lcdBuffer[0],16);
	clearBuffer(lcdBuffer[1],16);
	clearBuffer(lcdBuffer[2],16);
	clearBuffer(lcdBuffer[3],16);

	strncpy(lcdBuffer[0], tempBuffer[0],16);
	strncpy(lcdBuffer[1], tempBuffer[1],16);
	strncpy(lcdBuffer[2], tempBuffer[2],16);
	strncpy(lcdBuffer[3], tempBuffer[3],16);
	Display(lcdBuffer[0], lcdBuffer[1], lcdBuffer[2], lcdBuffer[3]);

	while(PINA == 0);
	while(PINA != 0);
	SEI();

}*/


extern uint8_t rx_done;

extern void delay(unsigned long delay);
/*{
 unsigned long i;

 for (i = 0; i < delay; i++)
 {
  NOP();
 }
}*/

/*void clearBuffer(char *buffer, uint8_t size)
{
	for(uint8_t i = 0; i < size; i++) buffer[i] = 0;
}*/

#if(dbgUi == 0)
/***********************************************************
 *			Writing data uint8_ts to LCD Display
 ***********************************************************/
void LCD_data(uint8_t data)
{
	//if('0' <= data && data <= '~')
	{
		PORTD = data;
		LcdDataEn();
		LcdWrite();
		//  LcdInstrEn();
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
 *		Inc/Dec effect parameter value
 *		count MUST be a global variable
 ***********************************************************/
void RotCount(uint8_t dir, uint8_t *count)
{
	uint8_t change;

	if ((dir == 1) && (*count < 100))
	{
		(*count)++;
	}
	else if ((dir == 2) && (*count > 0))
	{
		(*count)--;
	}
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
#endif

uint8_t internalDisplayLineIndex = 0;
uint8_t receiveState = 0;

ISR(SPI_STC_vect)
{

	/*static uint8_t displayLineCharIndex;
	static uint8_t internalDisplayLineIndex;
	static uint8_t receiveState;*/
	char receivedChar;


	receivedChar = SPDR;
	switch(receiveState)
	{
		case 0: // start recieve: first recieved character is LCD line number
			internalDisplayLineIndex = receivedChar;
			displayLineCharIndex = 0;
			receiveState = 1;
			break;
		case 1: // recieved character is part of string

			if(receivedChar != 0/*(PINB & BIT(SPI_nCS)) == 0*/)
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
				//strncpy(lcdBuffer[displayLineIndex], displayLine, 19);
				displayLineCharIndex = 0;

			}

			break;
		default:;
	}

}
/***********************************************************
 *		Writing strings to LCD Display
 ***********************************************************/
int lcdBufferHash[4];
/*void Display(uint8_t *line1, uint8_t *line2, uint8_t *line3, uint8_t *line4)
{
	uint8_t n=0;
	uint8_t i=0;

	int hashDummy;
	int lineHash;

#if(dbgUi == 0)
	lineHash = 0;
	for(i = 0; line1[i] != 0 && i < 20; i++)
	{
		lineHash += line1[i];
	}
	if(line1 != 0)//if(lineHash != lcdBufferHash[0])
	{
		lcdBufferHash[0] = lineHash;
		LCD_instr(0x01);
		LCD_instr(0b00000110);
		while((*(line1 + n) != '\0') && (n < 20))
		{
			LCD_data(*(line1 + n));
			//delay(500);
			n++;
		}
	}

	lineHash = 0;
	for(i = 0; line2[i] != 0 && i < 20; i++)
	{
		lineHash += line2[i];
	}
	if(line2 != 0)//if(lineHash != lcdBufferHash[1])
	{
		lcdBufferHash[1] = lineHash;
		n=0;
		LCD_instr(SET_DDRAM_ADDRESS + LCD_LINE2_ADDR);
		while((*(line2 + n) != '\0') && (n < 20))
		{
			LCD_data(*(line2 + n));
			//delay(200);
			n++;
		}
	}

	lineHash = 0;
	for(i = 0; line3[i] != 0 && i < 20; i++)
	{
		lineHash += line3[i];
	}
	if(line3 != 0)//if(lineHash != lcdBufferHash[2])
	{
		lcdBufferHash[2] = lineHash;
		n=0;
		LCD_instr(SET_DDRAM_ADDRESS + LCD_LINE3_ADDR);
		while ((*(line3 + n) != '\0')  && (n < 20))
		{
			LCD_data(*(line3 + n));
			//delay(200);
			n++;
		}
	}

	lineHash = 0;
	for(i = 0; line4[i] != 0 && i < 20; i++)
	{
		lineHash += line4[i];
	}
	if(line4 != 0)//if(lineHash != lcdBufferHash[3])
	{
		lcdBufferHash[3] = lineHash;
		n=0;
		LCD_instr(SET_DDRAM_ADDRESS + LCD_LINE4_ADDR);
		while((*(line4 + n) != '\0') && (n < 20))
		{
			LCD_data(*(line4 + n));
			//delay(200);
			n++;
		}
	}

#else
	printf("***********************************************");
	printf("LCD0: %s\n", line1);
	printf("LCD1: %s\n", line2);
	printf("***********************************************");
#endif
}*/

void Display(uint8_t lineIndex, char *line)
{
	uint8_t n=0;
	uint8_t i=0;

	int hashDummy;

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
		//delay(500);
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

