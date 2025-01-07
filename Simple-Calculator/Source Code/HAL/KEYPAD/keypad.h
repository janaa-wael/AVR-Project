/*
 * KEYPAD.h
 *
 * Created: 10/8/2024 7:44:57 PM
 *  Author: Jana Wael
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIB/std_types.h"
#include "../../LIB/common_macros.h"

/* NUMBER OF ROWS AND COLUMNS */
#define KEYPAD_ROW_PORT				PORTB_ID
#define KEYPAD_COL_PORT				PORTD_ID

#define COL_PORT_OUTPUT				0x0F
#define ROW_PORT_INPUT				0x00

/* PORT CONFIGURATIONS */
#define KEYPAD_R0_PIN			0
#define KEYPAD_R1_PIN			1
#define KEYPAD_R2_PIN			2
#define KEYPAD_R3_PIN			3

#define KEYPAD_C0_PIN			0
#define KEYPAD_C1_PIN			1
#define KEYPAD_C2_PIN			2
#define KEYPAD_C3_PIN			3

#define	COL_INIT				0
#define COL_FINAL				3
#define ROW_INIT				0
#define ROW_FINAL				3

#define KEYPAD_NUM_ROWS 		4
#define KEYPAD_NUM_COLS			4

#define KEYPAD_BUTTON_PRESSED		0
#define KEYPAD_BUTTON_RELEASED		1

#define KPD_VALUES     {{'7','8','9','/'},\
		{'4','5','6','*'},\
		{'1','2','3','-'},\
		{'c','0','=','+'}}

void KEYPAD_voidInit(void);
uint8 KEYPAD_READ(void);


#endif /* KEYPAD_H_ */
