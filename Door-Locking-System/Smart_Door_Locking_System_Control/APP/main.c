/*
 * main.c
 *
 *  Created on: Nov 2, 2024
 *      Author: hp
 */
#include "APP.h"
#include "../MCAL/UART/uart.h"
#include <util/delay.h>

int main()
{
	MCAL_INIT();
	HAL_INIT();
	uint8 change_pass_flag = 0;
	while(1)
	{
		SetupSystemPass();
		change_pass_flag = 0;
		while(change_pass_flag == 0)
			Receive_MainOptionChar(&change_pass_flag);

	}
}
