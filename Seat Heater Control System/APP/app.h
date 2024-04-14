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











/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/





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