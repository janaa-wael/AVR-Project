/*
 * main.c
 *
 *  Created on: Oct 13, 2024
 *      Author: hp
 */

#include "APP.h"
#include <util/delay.h>

int main()
{

	MCAL_Init();
	HAL_Init();
	LCD_constant_msg();


	while(1)
	{
		LCD_Print_Distance();
		_delay_ms(1);
	}
}
