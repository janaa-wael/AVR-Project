/*
 * APP.h
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "../HAL/LED/LED.h"
#include "../HAL/MOTOR/motor.h"
#include "../HAL/BUZZER/BUZZER.h"
#include "../HAL/FLAME_SENSOR/FLAME_SENSOR.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/LDR/LDR.h"
#include "../HAL/Temp_Sensor/lm35_sensor.h"

void MCAL_INIT(void);
void HAL_INIT(void);
void LCD_STATIC_TXT();
void DC_MOTOR_SPIN_CONTROL(uint16 TmpSensor_reading);
void UPDATE_1ST_LINE_LCD(uint16 TmpSensor_reading);
void UPDATE_2ND_LINE_LCD(uint16 TmpSensor_reading, uint16 LDR_reading);
void Fire_Detected(void);

#endif /* APP_APP_H_ */
