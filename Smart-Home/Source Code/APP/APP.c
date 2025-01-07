/*
 * APP.c
 *
 *  Created on: Oct 6, 2024
 *      Author: hp
 */

#include "../HAL/LED/LED.h"
#include "../HAL/MOTOR/motor.h"
#include "../HAL/BUZZER/BUZZER.h"
#include "../HAL/FLAME_SENSOR/FLAME_SENSOR.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/LDR/LDR.h"
#include "../HAL/Temp_Sensor/lm35_sensor.h"
#include "../MCAL/ADC/adc.h"


void MCAL_INIT(void)
{
	ADC_init();
}

void HAL_INIT(void)
{
	LEDS_init();
	LCD_init();
	Buzzer_init();
	FlameSensor_init();
	DcMotor_Init();

}

void Iterate_On_Leds(uint16 LDR_reading)
{
	if(LDR_reading < 15)
	{
		LED_on(LED_RED_ID);
		LED_on(LED_BLUE_ID);
		LED_on(LED_GREEN_ID);
	}
	else if(LDR_reading < 50)
	{
		LED_on(LED_RED_ID);
		LED_off(LED_BLUE_ID);
		LED_on(LED_GREEN_ID);
	}
	else if(LDR_reading < 70)
	{
		LED_on(LED_RED_ID);
		LED_off(LED_BLUE_ID);
		LED_off(LED_GREEN_ID);
	}
	else
	{
		LED_off(LED_RED_ID);
		LED_off(LED_BLUE_ID);
		LED_off(LED_GREEN_ID);
	}

}

void LCD_STATIC_TXT()
{
	LCD_moveCursor(0,4);
	LCD_displayString("FAN IS ");
	LCD_moveCursor(1,0);
	LCD_displayString("Tmp=   C,LDR=   %");

}



void DC_MOTOR_SPIN_CONTROL(uint16 TmpSensor_reading)
{
	if(TmpSensor_reading < 25)
	{
		DcMotor_Rotate(STOP,0);
	}
	else if(TmpSensor_reading < 30)
	{
		DcMotor_Rotate(CLKWISE,0.25*255);
	}
	else if(TmpSensor_reading < 35)
	{
		DcMotor_Rotate(CLKWISE,0.50*255);
	}
	else if(TmpSensor_reading < 40)
	{
		DcMotor_Rotate(CLKWISE,0.75*255);
	}
	else
	{
		DcMotor_Rotate(CLKWISE,1*255);
	}
}

void UPDATE_1ST_LINE_LCD(uint16 TmpSensor_reading)
{
	LCD_moveCursor(0,10);
	if(TmpSensor_reading<25)
	{
		LCD_displayString(" OFF");
	}
	else
	{
		LCD_displayString(" ON ");
	}
}

void UPDATE_2ND_LINE_LCD(uint16 TmpSensor_reading, uint16 LDR_reading)
{
	LCD_moveCursor(1,4);
	if(TmpSensor_reading > 99)
	{
		LCD_intgerToString(TmpSensor_reading);
	}
	else if (TmpSensor_reading > 9)
	{
		LCD_displayCharacter(' ');
		LCD_intgerToString(TmpSensor_reading);
	}
	else if(TmpSensor_reading >= 0)
	{
		LCD_displayString("  ");
		LCD_intgerToString(TmpSensor_reading);
	}

	if(LDR_reading < 15)
	{
		LED_on(LED_BLUE_ID);
		LED_on(LED_GREEN_ID);
		LED_on(LED_RED_ID);
	}
	else if(LDR_reading <= 50)
	{
		LED_on(LED_GREEN_ID);
		LED_on(LED_RED_ID);
		LED_off(LED_BLUE_ID);
	}
	else if(LDR_reading <= 70)
	{
		LED_on(LED_RED_ID);
		LED_off(LED_GREEN_ID);
		LED_off(LED_BLUE_ID);
	}
	else
	{
		LED_off(LED_RED_ID);
		LED_off(LED_GREEN_ID);
		LED_off(LED_BLUE_ID);
	}
	LCD_moveCursor(1,13);

	LCD_intgerToString(LDR_reading);
	if(LDR_reading < 10)
		{
		LCD_displayString(" %");
		}
	else if(LDR_reading <= 99)
	LCD_displayString("%");

}

void Fire_Detected()
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("CRITICAL ALERT!!");
	Buzzer_on();
	while(FlameSensor_getValue());
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_STATIC_TXT();
	Buzzer_off();

}
