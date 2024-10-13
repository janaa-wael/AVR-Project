/*
 * main.c
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */

#include "../HAL/LCD/lcd.h"
#include "../HAL/LED/LED.h"
#include "../HAL/LDR/LDR.h"
#include "../HAL/Temp_Sensor/lm35_sensor.h"
#include "../HAL/FLAME_SENSOR/FLAME_SENSOR.h"
#include "../HAL/MOTOR/motor.h"
#include "../HAL/BUZZER/BUZZER.h"
#include <util/delay.h>
#include "APP.h"
#include <avr/io.h>

uint16 LDR_reading, TmpSensor_reading, FlameSensor_reading, fire_flag = 0;

int main()
{

	MCAL_INIT();
	HAL_INIT();
	LCD_STATIC_TXT();
	//Buzzer_on();

	while(1)
	{
		fire_flag = 0;
		//LCD_sendCommand(LCD_CLEAR_COMMAND);
		//LDR_reading = LDR_getLightIntensity();
		TmpSensor_reading = LM35_getTemperature();
		LDR_reading = LDR_getLightIntensity();
		FlameSensor_reading = FlameSensor_getValue();
		if(FlameSensor_reading == 1)
		{
			Fire_Detected();
		}

		DC_MOTOR_SPIN_CONTROL(TmpSensor_reading);
		UPDATE_1ST_LINE_LCD(TmpSensor_reading);
		UPDATE_2ND_LINE_LCD(TmpSensor_reading, LDR_reading);

		//_delay_us(500);
	}
}


