/*
 * app.c
 *
 *  Created on: Apr 14, 2024
 *      Author: Ashraf
 */

#include "app.h"
#include "app_private.h"
#include "Port.h"
#include "Dio.h"
#include "uart0.h"
#include "GPTM.h"
#include "adc.h"
#include "heater.h"
#include "lm35.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"





/* function prototypes */
void Task(void *pvParameters);
void vButtonTask(void *pvParameters);
void vRunTimeMeasurementsTask(void *pvParameters);
void vTempReadTask(void *pvParameters);
void vControlTask(void *pvParameters);


/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

/* --------------Tasks Handlers-------------- */
TaskHandle_t Driving_Wheel_Button_Task_Handler;
TaskHandle_t Driver_Button_Task_Handler;
TaskHandle_t Passanger_Button_Task_Handler;
TaskHandle_t Driver_Seat_Temp_Read_Task_Handler;
TaskHandle_t Passanger_Seat_Temp_Read_Task_Handler;
TaskHandle_t Driver_Seat_Heater_Task_Handler;
TaskHandle_t Passanger_Seat_Heater_Task_Handler;
TaskHandle_t Display_Task_Handler;
TaskHandle_t Control_Task_Handler;
TaskHandle_t Failure_Task_Handler;


/* Diagnostics */
Diagnostics_type DiagnosticsArray[512];
uint16 Diagnostics_index = 0;


/* Global Variables for Heating States */
uint8_t g_ucDriverSeatState = 0;
uint8_t g_ucPassengerSeatState = 0;

/* Parameters for Button Tasks */
ButtonTaskParameterType DrivingWheelButtonTaskParameter = {DioConf_SW1_CHANNEL_NUM, &g_ucDriverSeatState};
ButtonTaskParameterType DriverSeatConsoleButtonTaskParameter = {DioConf_SW1_CHANNEL_NUM, &g_ucDriverSeatState};
ButtonTaskParameterType PassengerSeatConsoleButtonTaskParameter = {DioConf_SW2_CHANNEL_NUM, &g_ucPassengerSeatState};


/* Global Variables for Temperature */
uint8 g_u8DriverSeatTemp = 0;
uint8 g_u8PassengerSeatTemp = 0;

/* Parameters for Temp Read Tasks */
TempReadTaskParameterType DriverSeatTempReadTaskParameter = {SENSOR_1_CHANNEL_ID, &g_u8DriverSeatTemp};
TempReadTaskParameterType PassengerSeatTempReadTaskParameter = {SENSOR_2_CHANNEL_ID, &g_u8PassengerSeatTemp};


/* Global Variables for Heating Intensity */
uint8_t g_u8DriverSeatHeaterIntensity = 0;
uint8_t g_u8PassengerSeatHeaterIntensity = 0;

/* Parameters for Control Tasks */
ControlTaskParameterType DriverSeatControlTaskParameter = {DRIVER_SEAT, &g_ucDriverSeatState, &g_u8DriverSeatTemp, &g_u8DriverSeatHeaterIntensity};
ControlTaskParameterType PassangerSeatControlTaskParameter = {PASSENGER_SEAT, &g_ucPassengerSeatState, &g_u8PassengerSeatTemp, &g_u8PassengerSeatHeaterIntensity};


/*******************************************************************************
 *                             Functions Definition                            *
 *******************************************************************************/

void APP_start(void)
{
    /* Start the scheduler */
    vTaskStartScheduler();
}



void APP_init(void)
{
    /* --------------Initialize the peripherals-------------- */

    /* Initialize Port */
    Port_Init(&Port_Configuration);

    /* Initialize Dio */
    Dio_Init(&Dio_Configuration);

    /* Initialize UART */
    UART0_Init();

    /* Initialize ADC */
    ADC0_EnableCLock();



    /* --------------Tasks Creation-------------- */

    xTaskCreate(vButtonTask,
                "Driving Wheel Button Task",
                256,
                (void *)&DrivingWheelButtonTaskParameter,
                HIGH_PRIORITY,
                &Driving_Wheel_Button_Task_Handler);


    xTaskCreate(vButtonTask,
                "Driver Seat Console Button Task",
                256,
                (void *)&DriverSeatConsoleButtonTaskParameter,
                HIGH_PRIORITY,
                &Driver_Button_Task_Handler);


    xTaskCreate(vButtonTask,
                "Passenger Seat Console Button Task",
                256,
                (void *)&PassengerSeatConsoleButtonTaskParameter,
                HIGH_PRIORITY,
                &Passanger_Button_Task_Handler);


    xTaskCreate(vTempReadTask,
                "Driver Seat Temp Read Task",
                256,
                (void *)&DriverSeatTempReadTaskParameter,
                MEDIUM_PRIORITY,
                &Driver_Seat_Temp_Read_Task_Handler);


    xTaskCreate(vTempReadTask,
                "Passenger Seat Temp Read Task",
                256,
                (void *)&PassengerSeatTempReadTaskParameter,
                MEDIUM_PRIORITY,
                &Passanger_Seat_Temp_Read_Task_Handler);


    xTaskCreate(Task,
                "Driver Seat Heater Task",
                256,
                NULL,
                MEDIUM_PRIORITY,
                &Driver_Seat_Heater_Task_Handler);


    xTaskCreate(Task,
                "Passenger Seat Heater Task",
                256,
                NULL,
                MEDIUM_PRIORITY,
                &Passanger_Seat_Heater_Task_Handler);


    xTaskCreate(Task,
                "Display Task",
                256,
                NULL,
                LOW_PRIORITY,
                &Display_Task_Handler);


    xTaskCreate(vControlTask,
                "Driver Seat Control Task",
                256,
                (void *)&DriverSeatControlTaskParameter,
                MEDIUM_PRIORITY,
                &Control_Task_Handler);


    xTaskCreate(vControlTask,
                "Passenger Seat Control Task",
                256,
                (void *)&PassangerSeatControlTaskParameter,
                MEDIUM_PRIORITY,
                &Control_Task_Handler);


    xTaskCreate(Task,
                "Failure Handling Task",
                256,
                NULL,
                HIGH_PRIORITY,
                &Failure_Task_Handler);


    xTaskCreate(vRunTimeMeasurementsTask,
                "Run time Measurements",
                256,
                NULL,
                LOW_PRIORITY,
                NULL);

}


/* ------- Temp Task ------- */
void Task(void *pvParameters)
{

    for(;;)
    {

    }

}





void vButtonTask(void *pvParameters)
{
    ButtonTaskParameterType* Button = pvParameters;
    int flag = 0;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint8 ucButtonState;
    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, BUTTON_TASK_PERIODICITY );
        ucButtonState = Dio_ReadChannel( Button->Channel);

        /* If the button is pressed */
        if(ucButtonState == STD_LOW)
        {
            /* For Debouncing */
            vTaskDelay(pdMS_TO_TICKS(30));
            ucButtonState = Dio_ReadChannel( Button->Channel);
            if(ucButtonState == STD_LOW)
            {
                if( flag == 0 )
                {
                    /* Increase the state by 1 */
                    *(Button->ButtonStateVarAddress) = (*(Button->ButtonStateVarAddress)+1) %4;

                    /* Adding Diagnostics */
                    taskENTER_CRITICAL();/* ----------- Critical Section ----------- */

                    DiagnosticsArray[Diagnostics_index].Action = *(Button->ButtonStateVarAddress);
                    DiagnosticsArray[Diagnostics_index].TimeStamp = GPTM_WTimer0Read();
                    Diagnostics_index++;

                    taskEXIT_CRITICAL(); /* ----------- Critical Section ----------- */

                }
                /* raise the flag so it doesn't change the state again */
                flag = 1;
            }

        }
        /* If the button is not pressed */
        else
        {
            flag = 0;
        }


    }

}



void vTempReadTask(void *pvParameters)
{
    TempReadTaskParameterType *TempSensor = pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();

#if DEBUGGING_MODE_ACTIVATED == 1
    uint16_t ADC_Value = 0;
#endif

    for(;;)
    {

        vTaskDelayUntil( &xLastWakeTime, TEMP_READ_TASK_PERIODICITY );


#if DEBUGGING_MODE_ACTIVATED == 1
        /* Read ADC value */
        ADC_Value = ADC0_ReadChannel((channel_no)TempSensor->Channel);

        /* Get Temp Value and store it */
        *(TempSensor->TempVarAddress) = (float)ADC_Value * 45 / ADC_MAXIMUM_VALUE;
#else

        /* Read Temp Sensor */
        *(TempSensor->TempVarAddress) = LM35_getTemperature((channel_no)TempSensor->TempVarAddress);

#endif
    }

}




void vControlTask(void *pvParameters)
{
    ControlTaskParameterType *Seat = (ControlTaskParameterType *)pvParameters;
    uint8_t Temp = 0;
    uint8_t HeatingState = 0;
    uint8_t DesiredTemp = 0;
    signed char TempDiff = 0;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, CONTROL_TASK_PERIODICITY );
        Temp = *(Seat->SeatTempVarAddress);
        HeatingState = *(Seat->DesiredTempStateVarAddress);

        /* Check if Temp out of range */
        if (Temp > 40 || Temp < 5)
        {
            //signal an event to the failure Task

            continue;
        }

        /* Calculate Desired Temp */
        /* NOTE: can be wrapped in a function */
        switch( HeatingState )
        {
            case 0:
                DesiredTemp = Temp;
                break;

            case 1:
                DesiredTemp = 25;
                break;

            case 2:
                DesiredTemp = 30;
                break;

            case 3:
                DesiredTemp = 35;
                break;
        }

        /* Temp Difference */
        TempDiff = DesiredTemp - Temp;

        /* check for off */
        if(  TempDiff <= 2 )
        {
            *(Seat->HeatingIntensityLevel) = 0;
        }
        /* check for low */
        else if( TempDiff > 2 && TempDiff <= 5 )
        {
            *(Seat->HeatingIntensityLevel) = 1;
        }
        /* check for medium */
        else if( TempDiff > 5 && TempDiff <= 10 )
        {
            *(Seat->HeatingIntensityLevel) = 2;
        }
        /* check for High */
        else
        {
            *(Seat->HeatingIntensityLevel) = 3;
        }


    }


}



void vRunTimeMeasurementsTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    static uint8 cRuntimeStatBuffer[ 512 ];
    for (;;)
    {
        vTaskDelayUntil(&xLastWakeTime, RUNTIME_MEASUREMENTS_TASK_PERIODICITY);

        vTaskGetRunTimeStats( (char *)cRuntimeStatBuffer );

        taskENTER_CRITICAL();
        UART0_SendString("\r\nTask\t\tAbs\t\t%%\r\n");
        UART0_SendString( "-------------------------------------------\r\n" );
        UART0_SendString( cRuntimeStatBuffer );
        taskEXIT_CRITICAL();

    }
}



