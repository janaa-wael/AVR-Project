/*
 * LDR.h
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */

#ifndef HAL_LDR_LDR_H_
#define HAL_LDR_LDR_H_

#include "../../LIB/std_types.h"


#define SENSOR_CHANNEL_ID         0
#define SENSOR_MAX_VOLT_VALUE     2.56
#define SENSOR_MAX_VALUE	      100

uint16 LDR_getLightIntensity(void);

#endif /* HAL_LDR_LDR_H_ */
