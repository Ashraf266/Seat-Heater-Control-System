 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Ashraf
 ******************************************************************************/
 
 #include "Port.h"
 #include "Port_Regs.h"
 
#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || ( DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || ( DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigPin* Port_pinConfigPtr = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
STATIC void	 Get_Port_Pin_by_ID(const Port_ConfigPin* pinConfig, uint8 *portNum, uint8 *pinNum);


/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
	uint8 pinNum  = 0;
	uint8 portNum = 0;
	uint8 i = 0;
	boolean error = FALSE;
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
	
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	
	/* Check if the configuration pointer is NULL if null Report a Development Error */
	if( ConfigPtr == NULL_PTR)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}

#endif
	if( error == FALSE )
	{
		Port_pinConfigPtr = ConfigPtr->pins;
		
		/* Enable all Ports clock */
		SYSCTL_REGCGC2_REG |= 0x3F;
		delay = SYSCTL_REGCGC2_REG; /* Enabling clock requires a small delay */
		
		for( i=0 ; i<PORT_NUMBER_OF_PINS; i++ )
		{
			Get_Port_Pin_by_ID(&Port_pinConfigPtr[i], &portNum, &pinNum);
			
			/* Get PORT Base Address */
			   switch(portNum)
			{
				case  0: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
					break;
				case  1: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
					break;
				case  2: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
					break;
				case  3: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
					break;
				case  4: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
					break;
				case  5: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
					break;
			}
			
			
			if( ((portNum == 3) && (pinNum == 7)) || ((portNum == 5) && (pinNum == 0)) ) /* PD7 or PF0 */
			{
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;         /* Unlock the GPIOCR register */   
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
			}
			else if( (portNum == 2) && (pinNum <= 3) ) /* PC0 to PC3 */
			{
				/* Do Nothing ...  this is the JTAG pins */
			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for this pin */
			}
			
			
			/* setting up Pin Direction, initial value & internal resistors */
			if(Port_pinConfigPtr[i].pinDirection == PORT_PIN_OUT)
			{
				/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pinNum);                
				
				if( Port_pinConfigPtr[i].pinLevel == PORT_PIN_LEVEL_HIGH)
				{
					/* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pinNum);          
				}
				else
				{
					/* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pinNum);        
				}
			}
			else if(Port_pinConfigPtr[i].pinDirection == PORT_PIN_IN)
			{
				/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pinNum);             
				
				if(Port_pinConfigPtr[i].pinInternalResistor == PORT_PIN_INTERNAL_PULL_UP_RES_ACTIVE)
				{
					/* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pinNum);       
				}
				else if(Port_pinConfigPtr[i].pinInternalResistor == PORT_PIN_INTERNAL_PULL_DOWN_RES_ACTIVE)
				{
					/* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , pinNum);     
				}
				else
				{
					/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pinNum);     
					
					/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , pinNum);   
				}
			}
			else
			{
				/* Do Nothing */
			}


			/* setting up Pin Mode */
			switch( Port_pinConfigPtr[i].pinMode )
			{
				case PORT_PIN_MODE_DIO:
				
					/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pinNum);  
					
					/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pinNum);   
					
					/* Clear the PMCx bits for this pin */
					*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pinNum * 4));   
					
					/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pinNum);
					
					break;
					
				case PORT_PIN_MODE_ADC:
					
					/* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pinNum);  
					
					/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pinNum);   
					
					/* Clear the PMCx bits for this pin */
					*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pinNum * 4));   
					
					/* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pinNum);
					
					break;
					
				default:
				
					/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pinNum);  
					
					/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pinNum);   
					
					/* Clear the PMCx bits for this pin */
					*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pinNum * 4));
					
					/* Select the corresponding mode defined in the PBconfig structure */
					*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Port_pinConfigPtr[i].pinMode << (pinNum * 4));
					
					/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pinNum);
				
					break;
				
			}
			
			
		}		
		
		Port_Status = PORT_INITIALIZED;
	}
}



#if	(PORT_SET_PIN_DIRECTION_API == STD_ON)
	
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01 
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin       - 	Port Pin ID number
*                  Direction -  Port Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction 
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction )
{
	
	uint8 pinNum  = 0;
	uint8 portNum = 0;
	boolean error = FALSE;
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
	
#if (PORT_DEV_ERROR_DETECT == STD_ON)

	if( Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}
	
	if( Pin >= PORT_NUMBER_OF_PINS)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}
	
	if( Port_pinConfigPtr[Pin].pinDirectionChangable == PORT_PIN_DIRECTION_NOT_CHANGEABLE)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}

#endif

	if( error == FALSE )
	{

		Get_Port_Pin_by_ID(&Port_pinConfigPtr[Pin], &portNum, &pinNum);
		
		/* Get PORT Base Address */
		   switch(portNum)
		{
			case  0: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				break;
			case  1: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				break;
			case  2: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				break;
			case  3: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				break;
			case  4: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				break;
			case  5: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				break;
		}
		
		
		if( ((portNum == 3) && (pinNum == 7)) || ((portNum == 5) && (pinNum == 0)) ) /* PD7 or PF0 */
		{
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;         /* Unlock the GPIOCR register */   
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
		}
		else if( (portNum == 2) && (pinNum <= 3) ) /* PC0 to PC3 */
		{
			/* Do Nothing ...  this is the JTAG pins */
		}
		else
		{
			/* Do Nothing ... No need to unlock the commit register for this pin */
		}


		/* setting up Pin Direction */
		if(Direction == PORT_PIN_OUT)
		{
			/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pinNum);
		}
		
		else if(Direction == PORT_PIN_IN)
		{
			/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pinNum);
		}
		
		else
		{
			/* Do Nothing */
		}

	}
}

#endif


/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction. 
************************************************************************************/
void Port_RefreshPortDirection(void)
{
	
	uint8 pinNum  = 0;
	uint8 portNum = 0;
	uint8 i = 0;
	boolean error = FALSE;
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
	
#if (PORT_DEV_ERROR_DETECT == STD_ON)

	if( Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}

#endif

	if( error == FALSE )
	{
		for( i=0 ; i<PORT_NUMBER_OF_PINS; i++ )
		{
			
			Get_Port_Pin_by_ID(&Port_pinConfigPtr[i], &portNum, &pinNum);
			
			/* Get PORT Base Address */
			switch(portNum)
			{
				case  0: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
					break;
				case  1: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
					break;
				case  2: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
					break;
				case  3: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
					break;
				case  4: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
					break;
				case  5: 
					PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
					break;
			}
			
			
			if( ((portNum == 3) && (pinNum == 7)) || ((portNum == 5) && (pinNum == 0)) ) /* PD7 or PF0 */
			{
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;         /* Unlock the GPIOCR register */   
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
			}
			else if( (portNum == 2) && (pinNum <= 3) ) /* PC0 to PC3 */
			{
				/* Do Nothing ...  this is the JTAG pins */
			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for this pin */
			}


			/* setting up Pin Direction */
			if(Port_pinConfigPtr[i].pinDirection == PORT_PIN_OUT)
			{
				/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pinNum);
			}
			
			else if(Port_pinConfigPtr[i].pinDirection == PORT_PIN_IN)
			{
				/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pinNum);
			}
			
			else
			{
				/* Do Nothing */
			}
			
		}
	}

	
}


#if (PORT_VERSION_INFO_API == STD_ON)
	
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo	- Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module. 
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	
	boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

	if( Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}
	
	if( versioninfo == NULL_PTR)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}

#endif



	if( error == FALSE )
	{

		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}


}

#endif


#if (PORT_SET_PIN_MODE_API == STD_ON)

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin      - 	Port Pin ID number
*                  Mode 	-   New Port Pin mode to be set on port pin 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode. 
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
	
	uint8 pinNum  = 0;
	uint8 portNum = 0;
	boolean error = FALSE;
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

#if (PORT_DEV_ERROR_DETECT == STD_ON)

	if( Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}
	
	if( Pin >= PORT_NUMBER_OF_PINS)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}
	
	if( (Mode > 0x09) && (Mode != 0x0E) && (Mode != 0xFF) )
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}
	
	if( Port_pinConfigPtr[Pin].pinModeChangable == PORT_PIN_MODE_NOT_CHANGEABLE )
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
	}
	else
	{
		/* Do nothing */
	}

#endif


	if( error == FALSE )
	{


		Get_Port_Pin_by_ID(&Port_pinConfigPtr[Pin], &portNum, &pinNum);
		
		/* Get PORT Base Address */
		   switch(portNum)
		{
			case  0: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				break;
			case  1: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				break;
			case  2: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				break;
			case  3: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				break;
			case  4: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				break;
			case  5: 
				PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				break;
		}
		
		
		if( ((portNum == 3) && (pinNum == 7)) || ((portNum == 5) && (pinNum == 0)) ) /* PD7 or PF0 */
		{
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;         /* Unlock the GPIOCR register */   
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
		}
		else if( (portNum == 2) && (pinNum <= 3) ) /* PC0 to PC3 */
		{
			/* Do Nothing ...  this is the JTAG pins */
		}
		else
		{
			/* Do Nothing ... No need to unlock the commit register for this pin */
		}
	
	
		/* setting up Pin Mode */
		switch( Mode )
		{
			case PORT_PIN_MODE_DIO:
			
				/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pinNum);  
				
				/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pinNum);   
				
				/* Clear the PMCx bits for this pin */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pinNum * 4));   
				
				/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pinNum);
				
				break;
				
			case PORT_PIN_MODE_ADC:
				
				/* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pinNum);  
				
				/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pinNum);   
				
				/* Clear the PMCx bits for this pin */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pinNum * 4));   
				
				/* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pinNum);
				
				break;
				
			default:
			
				/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pinNum);  
				
				/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pinNum);   
				
				/* Clear the PMCx bits for this pin */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pinNum * 4));
				
				/* Select the corresponding mode */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (pinNum * 4));
				
				/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pinNum);
			
				break;
			
		}


	}

	
}

#endif


/*
 * Function to get the Port & Pin Number using pinID
 */
STATIC void	 Get_Port_Pin_by_ID(const Port_ConfigPin* pinConfig, uint8 *portNum, uint8 *pinNum)
{
	Port_PinType pinID = pinConfig->pinID;
	
	/* from A0 to E5 */
	if( pinID < 38 )
	{
		*portNum = pinID / 8;
		*pinNum  = pinID - (8 * (*portNum));
	}
	/* F0 to F4 */
	else
	{
		*portNum = 5;
		*pinNum = pinID - 38;
	}
	
}