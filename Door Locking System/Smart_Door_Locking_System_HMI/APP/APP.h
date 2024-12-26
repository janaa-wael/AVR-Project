/*
 * APP.h
 *
 *  Created on: Nov 1, 2024
 *      Author: hp
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "../LIB/common_macros.h"
#include "../LIB/std_types.h"

void MCAL_INIT(void);
void HAL_INIT(void);
void DISPLAY_CREATE_PASS_MSG(void);
void DISPLAY_REENTER_PASS_MSG(void);
void ENTER_PASS(uint8* password);
void CREATE_PASSWORD(void);
void SEND_PASSWORDS_TO_CTRL_ECU(void);
void PASSWORD_AUTHENTICATION();
void LCD_DISPLAY_MAIN_OPTIONS();
void CHECK_PASSWORDS();
void DOOR_LOCK_AND_UNLOCK(void);
void Display_Welcome_Msg(void);
void PASSWORD_REGISTRATION(void);
void SetUpSystemPassword(void);
void MainOptionsDisplay(uint8* change_pass_flag);
#endif /* APP_APP_H_ */
