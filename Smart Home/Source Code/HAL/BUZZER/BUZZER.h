/*
 * BUZZER.h
 *
 *  Created on: Oct 6, 2024
 *      Author: hp
 */

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

#define BUZZER_PORT		PORTD_ID
#define BUZZER_PIN		PIN3_ID


void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* HAL_BUZZER_BUZZER_H_ */
