/*
 * main.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Jana Wael
 */

#include <stdio.h>
#include "APP.h"

int main()
{
	HAL_Init();
	LCD_init_msg();
	while(1)
	{
		User_Formula_Input();
		Print_Equation_Result();
	}

}
