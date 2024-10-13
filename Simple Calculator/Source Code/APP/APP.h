/*
 * APP.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Jana Wael
 */

#ifndef APP_APP_H_
#define APP_APP_H_
#include "../LIB/std_types.h"

void HAL_Init(void);
void LCD_init_msg(void);
void User_Formula_Input(void);
uint8 Get_Keypad_Input(void);
uint8 ConvertCharToInt(uint8 input);
sint64 Equation_Simplification(void);
sint64 Second_Simplification(void);
void Print_Equation_Result(void);
void Reset_Arrays(void);
void RunTimeErrorMsg(void);
void User_Clearing_Screen(void);
#endif /* APP_APP_H_ */
