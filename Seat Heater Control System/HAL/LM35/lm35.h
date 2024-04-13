 /******************************************************************************
 *
 * Module: LM32_Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: Header file for the LM35 Sensor Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_1_CHANNEL_ID         PE1_PIN
#define SENSOR_2_CHANNEL_ID         PE2_PIN
#define SENSOR_MAX_VOLT_VALUE       1.5
#define SENSOR_MAX_TEMPERATURE      150

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*------------------------------------------------------------------
[Function Name]:  LM35_getTemperature
[Description]: Function responsible for calculate the temperature from the ADC digital value.
[Args]:
[in]	-Empty
[out]	-EMPTY
[in/out] -EMPTY
[Returns]: Nothing
------------------------------------------------------------------*/
uint8 LM35_getTemperature(uint8 Channel);

#endif /* LM35_SENSOR_H_ */