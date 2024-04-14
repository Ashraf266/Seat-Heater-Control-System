/*
 * app.h
 *
 *  Created on: Apr 14, 2024
 *      Author: Ashraf
 */
#ifndef APP_H_
#define APP_H_

#include "app_cfg.h"
#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/* Diagnostics */
#define FAILURE_OCCURED                     (0xFF)
#define HEATING_IS_OFF                      (0x00)
#define HEATING_LEVEL_CHANGED_TO_LOW        (0x01)
#define HEATING_LEVEL_CHANGED_TO_MED        (0x01)
#define HEATING_LEVEL_CHANGED_TO_HIGH       (0x01)





/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef struct
{
    uint32 TimeStamp;
    uint8  Action;

}Diagnostics_type;



/* Button Task Parameter Type */
typedef struct
{
    uint8 Channel;
    uint8 *ButtonStateVarAddress;

}ButtonTaskParameterType;

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/

/******************************************************************
[Function Name] : APP_init                                        *
[Description]   : Does All the initialization Required for the    *
                  application to start including creating the     *
                  tasks and initializing the peripherals          *
[Args]:         : NOTHING                                         *
[in]            : NOTHING                                         *
[out]           : NOTHING                                         *
[in/out]        : NOTHING                                         *
[Returns]       : void                                            *
*******************************************************************/
void APP_init(void);


/******************************************************************
[Function Name] : APP_start                                       *
[Description]   : Starts the application                          *
[Args]:         : NOTHING                                         *
[in]            : NOTHING                                         *
[out]           : NOTHING                                         *
[in/out]        : NOTHING                                         *
[Returns]       : void                                            *
*******************************************************************/
void APP_start(void);


#endif
