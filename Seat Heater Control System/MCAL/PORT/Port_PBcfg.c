 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.h
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Ashraf
 ******************************************************************************/
 
 #ifndef PORT_PBCFG_H
 #define PORT_PBCFG_H
 
 #include "Port.h"
 
 /*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION           (1U)
#define PORT_PBCFG_SW_MINOR_VERSION           (0U)
#define PORT_PBCFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)

/* AUTOSAR Version checking between Port.h and Port_PBcfg.h files */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != PORT_PBCFG_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_AR_RELEASE_MINOR_VERSION != PORT_PBCFG_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_AR_RELEASE_PATCH_VERSION != PORT_PBCFG_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port.h does not match the expected version"
#endif

/* Software Version checking between Port.h and Port_PBcfg.h files */
#if ((PORT_SW_MAJOR_VERSION != PORT_PBCFG_SW_MAJOR_VERSION)\
 ||  (PORT_SW_MINOR_VERSION != PORT_PBCFG_SW_MINOR_VERSION)\
 ||  (PORT_SW_PATCH_VERSION != PORT_PBCFG_SW_PATCH_VERSION))
  #error "The SW version of Port.h does not match the expected version"
#endif

const Port_ConfigType Port_Configuration = {
	   {{ PORT_PIN_A0_ID , PORT_PIN_MODE_U0Rx, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_A1_ID , PORT_PIN_MODE_U0Tx, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_OUT, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_A2_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_A3_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_A4_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_A5_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_A6_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_A7_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_PULL_UP_RES_ACTIVE, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B0_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B1_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B2_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B3_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B4_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B5_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B6_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_B7_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C0_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C1_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C2_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C3_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C4_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C5_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C6_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_C7_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D0_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D1_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D2_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D3_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D4_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D5_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D6_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_D7_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_E0_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_E1_ID , PORT_PIN_MODE_ADC, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_E2_ID , PORT_PIN_MODE_ADC, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_E3_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_E4_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_E5_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_F0_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_PULL_UP_RES_ACTIVE, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_F1_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_OUT, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_F2_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_OUT, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
		{ PORT_PIN_F3_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_OUT, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_RES_OFF, PORT_PIN_LEVEL_LOW},
	    { PORT_PIN_F4_ID , PORT_PIN_MODE_DIO, PORT_PIN_MODE_NOT_CHANGEABLE, PORT_PIN_IN, PORT_PIN_DIRECTION_NOT_CHANGEABLE, PORT_PIN_INTERNAL_PULL_UP_RES_ACTIVE, PORT_PIN_LEVEL_LOW}}
};

 
 #endif /* PORT_PBCFG_H */
