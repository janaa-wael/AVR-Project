/*
 * APP.h
 *
 *  Created on: Nov 2, 2024
 *      Author: hp
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "../LIB/std_types.h"

void MCAL_INIT(void);
void HAL_INIT(void);
void USER_REGISTRATION(void);
void Timer0_CallbackFunction(void);
void USER_AUTHENTICATION(void);
void Timer1_CallbackFunction(void);
void Receive_MainOptionChar(uint8* change_pass_flag);
void Save_Pass_In_EEPROM(uint8 *received_pass);
uint8 Cmp_Received_Pass(uint8 *rec_pass);
#endif /* APP_APP_H_ */
