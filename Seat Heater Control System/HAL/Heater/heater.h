/*
 * heater.h
 *
 *  Created on: Apr 14, 2024
 *      Author: Ashraf
 */

#ifndef HAL_HEATER_HEATER_H_
#define HAL_HEATER_HEATER_H_

#include "std_types.h"

#define HEATER_OFF                  (0u)
#define HEATER_LOW_INTENSITY        (1u)
#define HEATER_MEDUIM_INTENSITY     (2u)
#define HEATER_HIGH_INTENSITY       (3u)




void HEATER_setHeatingIntensity(uint8 HeatingIntensity);


#endif /* HAL_HEATER_HEATER_H_ */
