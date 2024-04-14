 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Ashraf
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Ashraf's ID = 266 */
#define PORT_VENDOR_ID    (266U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for Port_Init service */
#define PORT_INIT_SID           			(uint8)0x00

/* Service ID for Port_SetPinDirection service */
#define PORT_SET_PIN_DIRECTION_SID			(uint8)0x01

/* Service ID for Port_RefreshPortDirection service */
#define PORT_REFRESH_PORT_DIRECTION_SID		(uint8)0x02

/* Service ID for Port_GetVersionInfo service*/
#define PORT_GET_VERSION_INFO_SID           (uint8)0x03

/* Service ID for Port_SetPinMode service */
#define PORT_SET_PIN_MODE_SID           	(uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN				(uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE	(uint8)0x0B

/* API Port_Init service called with wrong parameter*/
#define PORT_E_PARAM_CONFIG				(uint8)0x0C

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE		(uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE		(uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT					(uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER			(uint8)0x10

/*******************************************************************************
 *                         	  Macros for Port Status                           *
 *******************************************************************************/
 /* Port initialization status */
#define PORT_INITIALIZED                		(1U)
#define PORT_NOT_INITIALIZED            		(0U)

/* Pin direction changeable ? */
#define PORT_PIN_DIRECTION_CHANGEABLE			(STD_ON)
#define PORT_PIN_DIRECTION_NOT_CHANGEABLE		(STD_OFF)

/* Pin mode changeable ? */
#define PORT_PIN_MODE_CHANGEABLE				(STD_ON)
#define PORT_PIN_MODE_NOT_CHANGEABLE			(STD_OFF)

/*	Internal resistor options */
#define PORT_PIN_INTERNAL_RES_OFF				(0U)
#define PORT_PIN_INTERNAL_PULL_UP_RES_ACTIVE	(1U)
#define PORT_PIN_INTERNAL_PULL_DOWN_RES_ACTIVE	(2U)

/* Pin Initial Level */
#define PORT_PIN_LEVEL_HIGH						(STD_HIGH)
#define PORT_PIN_LEVEL_LOW						(STD_LOW)

/* Pins ID in TM4C123GH6PM */
#define PORT_PIN_A0_ID    (Port_PinType)0
#define PORT_PIN_A1_ID    (Port_PinType)1
#define PORT_PIN_A2_ID    (Port_PinType)2
#define PORT_PIN_A3_ID    (Port_PinType)3
#define PORT_PIN_A4_ID    (Port_PinType)4
#define PORT_PIN_A5_ID    (Port_PinType)5
#define PORT_PIN_A6_ID    (Port_PinType)6
#define PORT_PIN_A7_ID    (Port_PinType)7
#define PORT_PIN_B0_ID    (Port_PinType)8
#define PORT_PIN_B1_ID    (Port_PinType)9
#define PORT_PIN_B2_ID    (Port_PinType)10
#define PORT_PIN_B3_ID    (Port_PinType)11
#define PORT_PIN_B4_ID    (Port_PinType)12
#define PORT_PIN_B5_ID    (Port_PinType)13
#define PORT_PIN_B6_ID    (Port_PinType)14
#define PORT_PIN_B7_ID    (Port_PinType)15
#define PORT_PIN_C0_ID    (Port_PinType)16
#define PORT_PIN_C1_ID    (Port_PinType)17
#define PORT_PIN_C2_ID    (Port_PinType)18
#define PORT_PIN_C3_ID    (Port_PinType)19
#define PORT_PIN_C4_ID    (Port_PinType)20
#define PORT_PIN_C5_ID    (Port_PinType)21
#define PORT_PIN_C6_ID    (Port_PinType)22
#define PORT_PIN_C7_ID    (Port_PinType)23
#define PORT_PIN_D0_ID    (Port_PinType)24
#define PORT_PIN_D1_ID    (Port_PinType)25
#define PORT_PIN_D2_ID    (Port_PinType)26
#define PORT_PIN_D3_ID    (Port_PinType)27
#define PORT_PIN_D4_ID    (Port_PinType)28
#define PORT_PIN_D5_ID    (Port_PinType)29
#define PORT_PIN_D6_ID    (Port_PinType)30
#define PORT_PIN_D7_ID    (Port_PinType)31
#define PORT_PIN_E0_ID    (Port_PinType)32
#define PORT_PIN_E1_ID    (Port_PinType)33
#define PORT_PIN_E2_ID    (Port_PinType)34
#define PORT_PIN_E3_ID    (Port_PinType)35
#define PORT_PIN_E4_ID    (Port_PinType)36
#define PORT_PIN_E5_ID    (Port_PinType)37
#define PORT_PIN_F0_ID    (Port_PinType)38
#define PORT_PIN_F1_ID    (Port_PinType)39
#define PORT_PIN_F2_ID    (Port_PinType)40
#define PORT_PIN_F3_ID    (Port_PinType)41
#define PORT_PIN_F4_ID    (Port_PinType)42

/* Mode List */
/* Pin Modes available for all Pins of TM4C123GH6PM */
#define PORT_PIN_MODE_ADC						(Port_PinModeType)0xFF
#define PORT_PIN_MODE_DIO						(Port_PinModeType)0x00

#define PORT_PIN_MODE_U0Rx						(Port_PinModeType)0x01
#define PORT_PIN_MODE_U0Tx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U1Rx_B0                   (Port_PinModeType)0x01
#define PORT_PIN_MODE_U1Tx_B1                   (Port_PinModeType)0x01
#define PORT_PIN_MODE_TCK                       (Port_PinModeType)0x01
#define PORT_PIN_MODE_SWCLK                     (Port_PinModeType)0x01
#define PORT_PIN_MODE_TMS                       (Port_PinModeType)0x01
#define PORT_PIN_MODE_SWDIO                     (Port_PinModeType)0x01
#define PORT_PIN_MODE_TDI                       (Port_PinModeType)0x01
#define PORT_PIN_MODE_TDO                       (Port_PinModeType)0x01
#define PORT_PIN_MODE_SWO                       (Port_PinModeType)0x01
#define PORT_PIN_MODE_U4Rx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U4Tx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U3Rx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U3Tx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_SSI3Clk                   (Port_PinModeType)0x01
#define PORT_PIN_MODE_SSI3Fss                   (Port_PinModeType)0x01
#define PORT_PIN_MODE_SSI3Rx                    (Port_PinModeType)0x01
#define PORT_PIN_MODE_SSI3Tx                    (Port_PinModeType)0x01
#define PORT_PIN_MODE_U6Rx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U6Tx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U2Rx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U2Tx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U7Rx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U7Tx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U5Rx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U5Tx                      (Port_PinModeType)0x01
#define PORT_PIN_MODE_U1RTS_F0                  (Port_PinModeType)0x01
#define PORT_PIN_MODE_U1CTS_F1                  (Port_PinModeType)0x01

#define PORT_PIN_MODE_SSI0Clk					(Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI0Fss                   (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI0Rx                    (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI0Tx                    (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI2Clk                   (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI2Fss                   (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI2Rx                    (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI2Tx                    (Port_PinModeType)0x02
#define PORT_PIN_MODE_U1Rx_C4                   (Port_PinModeType)0x02
#define PORT_PIN_MODE_U1Tx_C5                   (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI1Clk                   (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI1Fss                   (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI1Rx                    (Port_PinModeType)0x02
#define PORT_PIN_MODE_SSI1Tx                    (Port_PinModeType)0x02

#define PORT_PIN_MODE_I2C1SCL					(Port_PinModeType)0x03
#define PORT_PIN_MODE_I2C1SDA                   (Port_PinModeType)0x03
#define PORT_PIN_MODE_I2C0SCL                   (Port_PinModeType)0x03
#define PORT_PIN_MODE_I2C0SDA                   (Port_PinModeType)0x03
#define PORT_PIN_MODE_I2C3SCL                   (Port_PinModeType)0x03
#define PORT_PIN_MODE_I2C3SDA                   (Port_PinModeType)0x03
#define PORT_PIN_MODE_I2C2SCL                   (Port_PinModeType)0x03
#define PORT_PIN_MODE_I2C2SDA                   (Port_PinModeType)0x03
#define PORT_PIN_MODE_CAN0Rx_F0                 (Port_PinModeType)0x03
#define PORT_PIN_MODE_CAN0Tx_F3                 (Port_PinModeType)0x03

#define PORT_PIN_MODE_M0PWM2					(Port_PinModeType)0x04
#define PORT_PIN_MODE_M0PWM3					(Port_PinModeType)0x04
#define PORT_PIN_MODE_M0PWM0                    (Port_PinModeType)0x04
#define PORT_PIN_MODE_M0PWM1                    (Port_PinModeType)0x04
#define PORT_PIN_MODE_M0PWM6                    (Port_PinModeType)0x04
#define PORT_PIN_MODE_M0PWM7                    (Port_PinModeType)0x04
#define PORT_PIN_MODE_M0FAULT0                  (Port_PinModeType)0x04
#define PORT_PIN_MODE_M0PWM4                    (Port_PinModeType)0x04
#define PORT_PIN_MODE_M0PWM5                    (Port_PinModeType)0x04

#define PORT_PIN_MODE_M1PWM2					(Port_PinModeType)0x05
#define PORT_PIN_MODE_M1PWM3					(Port_PinModeType)0x05
#define PORT_PIN_MODE_M1PWM0                    (Port_PinModeType)0x05
#define PORT_PIN_MODE_M1PWM1                    (Port_PinModeType)0x05
#define PORT_PIN_MODE_M1PWM4                    (Port_PinModeType)0x05
#define PORT_PIN_MODE_M1PWM5                    (Port_PinModeType)0x05
#define PORT_PIN_MODE_M1PWM6                    (Port_PinModeType)0x05
#define PORT_PIN_MODE_M1PWM7                    (Port_PinModeType)0x05
#define PORT_PIN_MODE_M1FAULT0                  (Port_PinModeType)0x05

#define PORT_PIN_MODE_IDX1						(Port_PinModeType)0x06
#define PORT_PIN_MODE_PhA1						(Port_PinModeType)0x06
#define PORT_PIN_MODE_PhB1                      (Port_PinModeType)0x06
#define PORT_PIN_MODE_IDX0                      (Port_PinModeType)0x06
#define PORT_PIN_MODE_PhA0                      (Port_PinModeType)0x06
#define PORT_PIN_MODE_PhB0                      (Port_PinModeType)0x06

#define PORT_PIN_MODE_T2CCP0					(Port_PinModeType)0x07
#define PORT_PIN_MODE_T2CCP1					(Port_PinModeType)0x07
#define PORT_PIN_MODE_T3CCP0                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T3CCP1                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T1CCP0                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T1CCP1                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T0CCP0                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T0CCP1                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T4CCP0                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T4CCP1                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T5CCP0                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_T5CCP1                    (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT0CCP0                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT0CCP1                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT1CCP0                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT1CCP1                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT2CCP0                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT2CCP1                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT3CCP0                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT3CCP1                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT4CCP0                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT4CCP1                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT5CCP0                   (Port_PinModeType)0x07
#define PORT_PIN_MODE_WT5CCP1                   (Port_PinModeType)0x07

#define PORT_PIN_MODE_CAN1Rx					(Port_PinModeType)0x08
#define PORT_PIN_MODE_CAN1Tx					(Port_PinModeType)0x08
#define PORT_PIN_MODE_CAN0Rx_B4_E4              (Port_PinModeType)0x08
#define PORT_PIN_MODE_CAN0Tx_B5_E5              (Port_PinModeType)0x08
#define PORT_PIN_MODE_U1RTS_C4                  (Port_PinModeType)0x08
#define PORT_PIN_MODE_U1CTS_C5                  (Port_PinModeType)0x08
#define PORT_PIN_MODE_USB0EPEN                  (Port_PinModeType)0x08
#define PORT_PIN_MODE_USB0PFLT                  (Port_PinModeType)0x08
#define PORT_PIN_MODE_NMI                       (Port_PinModeType)0x08

#define PORT_PIN_MODE_C0o						(Port_PinModeType)0x09
#define PORT_PIN_MODE_C1o						(Port_PinModeType)0x09

#define PORT_PIN_MODE_TRD1						(Port_PinModeType)0x0E
#define PORT_PIN_MODE_TRD0						(Port_PinModeType)0x0E
#define PORT_PIN_MODE_TRCLK						(Port_PinModeType)0x0E


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinDirectionType used by the PORT APIs */
typedef enum
{
	PORT_PIN_IN,
	PORT_PIN_OUT
}Port_PinDirectionType;

/* Type definition for Port_PinModeType used by the PORT APIs */
typedef uint8 Port_PinModeType;

/* Type to determine if the pin direction is changable or not */
typedef boolean Port_PinDirectionChangeableType;

/* Type to determine the pin initial value level */
typedef uint8 Port_PinLevelValueType;

/* Type to determine if the pin mode is changable or not */
typedef boolean Port_PinModeChangeableType;

/* Type to determine if the pin internal resistor*/
typedef uint8 Port_InternalResistorType;

/* Structure contains a configuration of a single pin */
typedef struct
{
	Port_PinType					  pinID;
	Port_PinModeType 				  pinMode;
	Port_PinModeChangeableType		  pinModeChangable;
	Port_PinDirectionType			  pinDirection;
	Port_PinDirectionChangeableType	  pinDirectionChangable;	
	Port_InternalResistorType		  pinInternalResistor;
	Port_PinLevelValueType			  pinLevel;
}Port_ConfigPin;

/* Type definition for Port_ConfigType used by the PORT APIs */
typedef struct
{
	Port_ConfigPin	pins[PORT_NUMBER_OF_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Initializes the Port Driver module */
void Port_Init(const Port_ConfigType* ConfigPtr);

#if	(PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Sets the port pin direction  */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/* Refreshes port direction */
void Port_RefreshPortDirection(void);

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* Sets the port pin mode */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#if (PORT_VERSION_INFO_API == STD_ON)
/* Returns the version information of this module */
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
