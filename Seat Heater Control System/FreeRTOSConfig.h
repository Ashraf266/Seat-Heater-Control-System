/*
 * -------------------------------------------------------------------------
 * FreeRTOS Kernel Configuration File V1.0.0
 * Copyright (C) 2024 Edges For Training.  All Rights Reserved.
 * -------------------------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 * -------------------------------------------------------------------------
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "GPTM.h"
#include "std_types.h"

/******************************************************************************/
/* Scheduling behavior related definitions. **********************************/
/******************************************************************************/

/* configCPU_CLOCK_HZ must be set to the frequency of the clock that drives 
 * the peripheral used to generate the kernels periodic tick interrupt.
 * This is very often, but not always, equal to the main system clock frequency.
 * Default frequency in Tiva-C Micro-controllers is 16Mhz */
#define configCPU_CLOCK_HZ                    (( unsigned long )16000000)

/* configTICK_RATE_HZ sets frequency of the tick interrupt in Hz, so
 * in our case Tick time will be 1ms */
#define configTICK_RATE_HZ                    ((TickType_t)1000)

/* Size of the stack allocated to the Idle task. 128 Words = 512 Bytes */
#define configMINIMAL_STACK_SIZE              (128)

/* configMAX_PRIORITIES Sets the number of available task priorities.  Tasks can
 * be assigned priorities of 0 to (configMAX_PRIORITIES - 1).  Zero is the lowest
 * priority. */
#define configMAX_PRIORITIES                  (5)

/* Set configUSE_PREEMPTION to 1 to use pre-emptive scheduling. Set
 * configUSE_PREEMPTION to 0 to use co-operative scheduling. */
#define configUSE_PREEMPTION                  (1)                

/* When configUSE_16_BIT_TICKS is set to 1, TickType_t is defined
 * to be an unsigned 16-bit type. When configUSE_16_BIT_TICKS is set to 0, 
 * TickType_t is defined to be an unsigned 32-bit type. */
#define configUSE_16_BIT_TICKS                0

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

/* Sets the total size of the FreeRTOS heap, in bytes, when heap_1.c, heap_2.c
 * or heap_4.c are included in the build. This value is defaulted to 16384 bytes but
 * it must be tailored to each application. Note the heap will appear in the .bss
 * section. */
#define configTOTAL_HEAP_SIZE                 ((size_t)(16384))

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

/* Set the following INCLUDE_* constants to 1 to include the named API function,
 * or 0 to exclude the named API function.  Most linkers will remove unused
 * functions even when the constant is 1. */
#define INCLUDE_vTaskDelayUntil                 1

#define INCLUDE_vTaskDelay                      1

#define INCLUDE_vTaskSuspend                    1

/* Set the following configUSE_* constants to 1 to include the named feature in
 * the build, or 0 to exclude the named feature from the build. */
#define configUSE_APPLICATION_TASK_TAG         1
/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

/* Set the following configUSE_* constants to 1 to include the named hook
 * functionality in the build.  Set to 0 to exclude the hook functionality from the
 * build.  The application writer is responsible for providing the hook function
 * for any set to 1. */
#define configUSE_IDLE_HOOK                   0
#define configUSE_TICK_HOOK                   0

/******************************************************************************/
/* ARM Cortex-M Specific Definitions. *****************************************/
/******************************************************************************/

/* Tiva-C Micro-controllers use 3-bits as priority bits for each interrupt in NVIC PRI registers - 8 priority levels */
#define configPRIO_BITS                               3

/* The lowest interrupt priority that can be used */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY       7

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY  5

/* Interrupt priorities used by the kernel port layer itself (the tick and context switch performing interrupts).
 * This implementation is generic to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY               (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* It sets the interrupt priority above which FreeRTOS API calls must not be made.  
 * Interrupts above this priority are never disabled, so never delayed by RTOS activity. 
 * This implementation is generic to all Cortex-M ports, and do not rely on any particular library functions. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY          (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/******************************************************************************/
/* Debugging assistance. ******************************************************/
/******************************************************************************/

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/******************************************************************************/
/* FreeRTOS Runtime Statistics. ***********************************************/
/******************************************************************************/

#if 0
/* Set configGENERATE_RUN_TIME_STATS to 1 to enable collection of run-time statistics.
 * When this is done, both portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
 * and portGET_RUN_TIME_COUNTER_VALUE() or portALT_GET_RUN_TIME_COUNTER_VALUE(x) must also be defined. */
#define configGENERATE_RUN_TIME_STATS 1

/* portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() is defined to call the function that initializes
   the 32-bit timer */
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() GPTM_WTimer0Init()

/* portGET_RUN_TIME_COUNTER_VALUE() is defined to get the current run-time
 * timer value. The returned time value is 32-bits long, and is formed by subtracting the
 * current timer value from its max value because of our timer is counting down  */
#define portGET_RUN_TIME_COUNTER_VALUE()  GPTM_WTimer0Read()

/* Set to 1 to include the vTaskList() and vTaskGetRunTimeStats() functions in
 * the build.  Set to 0 to exclude these functions from the build.  These two
 * functions introduce a dependency on string formatting functions that would
 * otherwise not exist - hence they are kept separate.  Defaults to 0 if left
 * undefined. */
#define configUSE_STATS_FORMATTING_FUNCTIONS 1

/* Set configUSE_TRACE_FACILITY to include additional task structure members
 * are used by trace and visualization functions and tools.  Set to 0 to exclude
 * the additional information from the structures. Defaults to 0 if left
 * undefined. */
#define configUSE_TRACE_FACILITY             1

#endif

extern uint32 ullTasksOutTime[14];
extern uint32 ullTasksInTime[14];
extern uint32 ullTasksTotalTime[14];

#define traceTASK_SWITCHED_IN()                                    \
do{                                                                \
    uint32 taskInTag = (uint32)(pxCurrentTCB->pxTaskTag);          \
    ullTasksInTime[taskInTag] = GPTM_WTimer0Read();                \
}while(0);

#define traceTASK_SWITCHED_OUT()                                                                 \
do{                                                                                              \
    uint32 taskOutTag = (uint32)(pxCurrentTCB->pxTaskTag);                                       \
    ullTasksOutTime[taskOutTag] = GPTM_WTimer0Read();                                            \
    ullTasksTotalTime[taskOutTag] += ullTasksOutTime[taskOutTag] - ullTasksInTime[taskOutTag];   \
}while(0);

#endif /* FREERTOS_CONFIG_H */
