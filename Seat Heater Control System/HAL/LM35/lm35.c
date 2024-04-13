#include "lm35.h"
#include "adc.h"




uint8 LM35_getTemperature(uint8 Channel)
{
    volatile uint32 adc_value = 0;
	uint8 temp_value = 0;

	adc_value = ADC0_ReadChannel((channel_no)Channel);
	temp_value = (uint8)(((uint64)SENSOR_MAX_TEMPERATURE * adc_value * ADC_REF_VOLT_VALUE)/((float)SENSOR_MAX_VOLT_VALUE * ADC_MAXIMUM_VALUE));

	return temp_value;
}
