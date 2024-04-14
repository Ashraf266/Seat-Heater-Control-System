/*
 * app_cfg.h
 *
 *  Created on: Apr 14, 2024
 *      Author: Ashraf
 */

#ifndef APP_CFG_H_
#define APP_CFG_H_


/* Application running Mode */

#define DEBUGGING_MODE_ACTIVATED            (1u)



/* Priority Levels */
#define LOW_PRIORITY                    1
#define MEDIUM_PRIORITY                 2
#define HIGH_PRIORITY                   3



/* Tasks periodicity in Ticks */

#define BUTTON_TASK_PERIODICITY                         (150u)
#define TEMP_READ_TASK_PERIODICITY                      (5000u)
#define SEAT_HEATER_TASK_PERIODICITY                    (5000u)
#define CONTROL_TASK_PERIODICITY                        (5000u)
#define DISPLAY_TASK_PERIODICITY                        (5000u)
#define RUNTIME_MEASUREMENTS_TASK_PERIODICITY           (5000u)


#endif
