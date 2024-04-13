#ifndef ADC0_H_
#define ADC0_H_

#include "std_types.h"

#define ADC_MAXIMUM_VALUE           0xFFF
#define ADC_REF_VOLT_VALUE          3.3

typedef enum {
    PE3_PIN,PE2_PIN,PE1_PIN,PE0_PIN,PD3_PIN,PD2_PIN,PD1_PIN,PD0_PIN,
    PE5_PIN,PE4_PIN,PB4_PIN,PB5_PIN
} channel_no;


void ADC0_EnableCLock(void);
uint32 ADC0_ReadChannel(channel_no channel);


#endif /* ADC0_H_ */