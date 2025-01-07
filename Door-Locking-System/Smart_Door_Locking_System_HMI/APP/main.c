/*
 * main.c
 *
 *  Created on: Nov 1, 2024
 *      Author: hp
 */


#include "APP.h"
#include <util/delay.h>

int main()
{
	MCAL_INIT();
	HAL_INIT();
	Display_Welcome_Msg();
	uint8 change_pass_flag = 0;
	while(1)
	{
		SetUpSystemPassword();
		change_pass_flag = 0;
		while(change_pass_flag == 0)
			MainOptionsDisplay(&change_pass_flag);
	}
}
