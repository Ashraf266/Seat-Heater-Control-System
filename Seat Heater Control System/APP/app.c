/*
 * app.c
 *
 *  Created on: Apr 14, 2024
 *      Author: Ashraf
 */

#include "app.h"
#include "Port.h"
#include "Dio.h"
#include "uart0.h"
#include "GPTM.h"
#include "adc.h"
#include "heater.h"
#include "lm35.h"
#include "FreeRTOS.h"
#include "task.h"





/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/
void vButtonTask(void *pvParameters);
#if DEBUGGING_MODE_ACTIVATED == 1
void vRunTimeMeasurementsTask(void *pvParameters);
#endif
void vTempReadTask(void *pvParameters);
void vControlTask(void *pvParameters);
void vHeaterTask(void *pvParameters);
void vFailureHandlingTask(void *pvParameters);
void vDisplayTask(void *pvParameters);


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
TaskHandle_t Driver_Seat_Control_Task_Handler;
TaskHandle_t Passenger_Seat_Control_Task_Handler;
TaskHandle_t Driver_Seat_Failure_Task_Handler;
TaskHandle_t Passenger_Seat_Failure_Task_Handler;


/* Diagnostics */
Diagnostics_type DiagnosticsArray[512];
uint16 Diagnostics_index = 0;


/* Global Variables for Heating States */
uint8_t g_ucDriverSeatState = 0;
uint8_t g_ucPassengerSeatState = 0;

/* Parameters for Button Tasks */
ButtonTaskParameterType DrivingWheelButtonTaskParameter = {DioConf_SW1_CHANNEL_ID_INDEX, &g_ucDriverSeatState};
ButtonTaskParameterType DriverSeatConsoleButtonTaskParameter = {DioConf_SW3_CHANNEL_ID_INDEX, &g_ucDriverSeatState};
ButtonTaskParameterType PassengerSeatConsoleButtonTaskParameter = {DioConf_SW2_CHANNEL_ID_INDEX, &g_ucPassengerSeatState};


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


/* Parameters for Heater Tasks */
HeaterTaskParameterType DriverSeatHeaterTaskParameter = {DRIVER_SEAT
#if DEBUGGING_MODE_ACTIVATED
                                                         ,DioConf_BLUE_LED_CHANNEL_ID_INDEX,DioConf_GREEN_LED_CHANNEL_ID_INDEX
#endif
                                                         ,&g_u8DriverSeatHeaterIntensity
};
HeaterTaskParameterType PassengerSeatHeaterTaskParameter = {PASSENGER_SEAT
#if DEBUGGING_MODE_ACTIVATED
                                                            ,DioConf_BLUE_LED_CHANNEL_ID_INDEX, DioConf_GREEN_LED_CHANNEL_ID_INDEX
#endif
                                                            ,&g_u8PassengerSeatHeaterIntensity
};


/* Parameters for Failure Handling Tasks */
FailureTaskParameterType DriverSeatFailureTaskParameter = {DRIVER_SEAT,DioConf_RED_LED_CHANNEL_ID_INDEX
#if DEBUGGING_MODE_ACTIVATED
                                                         ,DioConf_BLUE_LED_CHANNEL_ID_INDEX, DioConf_GREEN_LED_CHANNEL_ID_INDEX
#endif
};
FailureTaskParameterType PassengerSeatFailureTaskParameter = {PASSENGER_SEAT,DioConf_RED_LED_CHANNEL_ID_INDEX
#if DEBUGGING_MODE_ACTIVATED
                                                            ,DioConf_BLUE_LED_CHANNEL_ID_INDEX, DioConf_GREEN_LED_CHANNEL_ID_INDEX
#endif
};



/* Run Time Measurements */
uint32 ullTasksOutTime[14];
uint32 ullTasksInTime[14];
uint32 ullTasksTotalTime[14];

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

    /* Initialize GPTM */
    GPTM_WTimer0Init();



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


    xTaskCreate(vHeaterTask,
                "Driver Seat Heater Task",
                256,
                (void *)&DriverSeatHeaterTaskParameter,
                MEDIUM_PRIORITY,
                &Driver_Seat_Heater_Task_Handler);


    xTaskCreate(vHeaterTask,
                "Passenger Seat Heater Task",
                256,
                (void *)&PassengerSeatHeaterTaskParameter,
                MEDIUM_PRIORITY,
                &Passanger_Seat_Heater_Task_Handler);


    xTaskCreate(vDisplayTask,
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
                &Driver_Seat_Control_Task_Handler);


    xTaskCreate(vControlTask,
                "Passenger Seat Control Task",
                256,
                (void *)&PassangerSeatControlTaskParameter,
                MEDIUM_PRIORITY,
                &Passenger_Seat_Control_Task_Handler);


    xTaskCreate(vFailureHandlingTask,
                "Driver Seat Failure Handling Task",
                256,
                (void *)&DriverSeatFailureTaskParameter,
                HIGH_PRIORITY,
                &Driver_Seat_Failure_Task_Handler);

    xTaskCreate(vFailureHandlingTask,
                "Passenger Seat Failure Handling Task",
                256,
                (void *)&PassengerSeatFailureTaskParameter,
                HIGH_PRIORITY,
                &Passenger_Seat_Failure_Task_Handler);

#if DEBUGGING_MODE_ACTIVATED == 1

    xTaskCreate(vRunTimeMeasurementsTask,
                "Run time Measurements",
                256,
                NULL,
                LOW_PRIORITY,
                NULL);
#endif


/* Set Tags */
    vTaskSetApplicationTaskTag( Driving_Wheel_Button_Task_Handler, ( void * ) 1 );
    vTaskSetApplicationTaskTag( Driver_Button_Task_Handler, ( void * ) 2 );
    vTaskSetApplicationTaskTag( Passanger_Button_Task_Handler, ( void * ) 3 );
    vTaskSetApplicationTaskTag( Driver_Seat_Temp_Read_Task_Handler, ( void * ) 4 );
    vTaskSetApplicationTaskTag( Passanger_Seat_Temp_Read_Task_Handler, ( void * ) 5 );
    vTaskSetApplicationTaskTag( Driver_Seat_Heater_Task_Handler, ( void * ) 6 );
    vTaskSetApplicationTaskTag( Passanger_Seat_Heater_Task_Handler, ( void * ) 7 );
    vTaskSetApplicationTaskTag( Passanger_Seat_Heater_Task_Handler, ( void * ) 8 );
    vTaskSetApplicationTaskTag( Display_Task_Handler, ( void * ) 9 );
    vTaskSetApplicationTaskTag( Driver_Seat_Control_Task_Handler, ( void * ) 10 );
    vTaskSetApplicationTaskTag( Passenger_Seat_Control_Task_Handler, ( void * ) 11 );
    vTaskSetApplicationTaskTag( Driver_Seat_Failure_Task_Handler, ( void * ) 12 );
    vTaskSetApplicationTaskTag( Passenger_Seat_Failure_Task_Handler, ( void * ) 13 );


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
        *(TempSensor->TempVarAddress) = LM35_getTemperature((channel_no)TempSensor->Channel);

#endif
    }

}




void vControlTask(void *pvParameters)
{
    ControlTaskParameterType *Seat = (ControlTaskParameterType *)pvParameters;
    uint8 Temp = 0;
    uint8 HeatingState = 0;
    uint8 DesiredTemp = 0;
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
            switch(Seat->Seat)
            {
            case 0:
                vTaskResume(Driver_Seat_Failure_Task_Handler);
                break;

            case 1:
                vTaskResume(Passenger_Seat_Failure_Task_Handler);
                break;
            }

            continue;
        }

        /* Calculate Desired Temp */
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



void vHeaterTask(void *pvParameters)
{
    HeaterTaskParameterType* Heater = pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, SEAT_HEATER_TASK_PERIODICITY );

        /* Turn on Heater on the intensity evaluated by the control task */
        HEATER_setHeatingIntensity(Heater->Seat, *(Heater->HeatingIntensityLevel));

#if DEBUGGING_MODE_ACTIVATED

        switch(*(Heater->HeatingIntensityLevel))
        {
        case 0:/* OFF */
            /* Turn off LEDs */
            Dio_WriteChannel(Heater->BlueLED_ID, STD_LOW);
            Dio_WriteChannel(Heater->GreenLED_ID, STD_LOW);
            break;
        case 1:/* Low Intensity */
            /* Turn on Green LED */
            Dio_WriteChannel(Heater->BlueLED_ID, STD_LOW);
            Dio_WriteChannel(Heater->GreenLED_ID, STD_HIGH);
            break;
        case 2:/* Med Intensity */
            /* Turn on Blue LED */
            Dio_WriteChannel(Heater->BlueLED_ID, STD_HIGH);
            Dio_WriteChannel(Heater->GreenLED_ID, STD_LOW);
            break;
        case 3:/* High Intensity */
            /* Turn on Green & Blue (Cyan)  LED */
            Dio_WriteChannel(Heater->BlueLED_ID, STD_HIGH);
            Dio_WriteChannel(Heater->GreenLED_ID, STD_HIGH);
            break;
        }

#endif

    }

}



void vFailureHandlingTask(void *pvParameters)
{
    FailureTaskParameterType *Fail = pvParameters;

    for(;;)
    {
        vTaskSuspend(NULL);
        switch(Fail->Seat)
        {
        case 0:

#if DEBUGGING_MODE_ACTIVATED
            Dio_WriteChannel(Fail->BlueLED_ID, STD_LOW);
            Dio_WriteChannel(Fail->GreenLED_ID, STD_LOW);
#endif
            /* Turn on Red LED */
            Dio_WriteChannel(Fail->RedLED_ID, STD_HIGH);

            /* Stop All Driver Seat Heating Activities */
            vTaskSuspend(Driving_Wheel_Button_Task_Handler);
            vTaskSuspend(Driver_Button_Task_Handler);
            vTaskSuspend(Driver_Seat_Temp_Read_Task_Handler);
            vTaskSuspend(Driver_Seat_Heater_Task_Handler);
            vTaskSuspend(Driver_Seat_Control_Task_Handler);

            g_ucDriverSeatState = 0xFF;
            g_u8DriverSeatHeaterIntensity = 0xFF;

            /* Adding Diagnostics */
            taskENTER_CRITICAL();/* ----------- Critical Section ----------- */

            DiagnosticsArray[Diagnostics_index].Action = DRIVER_SEAT_SYS_FAILURE;
            DiagnosticsArray[Diagnostics_index].TimeStamp = GPTM_WTimer0Read();
            Diagnostics_index++;

            taskEXIT_CRITICAL(); /* ----------- Critical Section ----------- */

            break;

        case 1:

#if DEBUGGING_MODE_ACTIVATED
            Dio_WriteChannel(Fail->BlueLED_ID, STD_LOW);
            Dio_WriteChannel(Fail->GreenLED_ID, STD_LOW);
#endif
            /* Turn on Red LED */
            Dio_WriteChannel(Fail->RedLED_ID, STD_HIGH);

            /* Stop All Passenger Seat Heating Activities */
            vTaskSuspend(Passanger_Button_Task_Handler);
            vTaskSuspend(Passanger_Seat_Temp_Read_Task_Handler);
            vTaskSuspend(Passanger_Seat_Heater_Task_Handler);
            vTaskSuspend(Passenger_Seat_Control_Task_Handler);

            g_ucPassengerSeatState = 0xFF;
            g_u8PassengerSeatHeaterIntensity = 0xFF;


            /* Adding Diagnostics */
            taskENTER_CRITICAL();/* ----------- Critical Section ----------- */

            DiagnosticsArray[Diagnostics_index].Action = PASSENGER_SEAT_SYS_FAILURE;
            DiagnosticsArray[Diagnostics_index].TimeStamp = GPTM_WTimer0Read();
            Diagnostics_index++;

            taskEXIT_CRITICAL(); /* ----------- Critical Section ----------- */

            break;
        }


    }

}


void vDisplayTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, DISPLAY_TASK_PERIODICITY );

        /* ------------- Driver Seat ------------- */
        if(g_u8DriverSeatTemp > 40 || g_u8DriverSeatTemp < 5)
        {
            UART0_SendString("Driver Seat Temperature: ");
            UART0_SendString("ERROR!!!\r\n");
        }
        else
        {
            UART0_SendString("Driver Seat Temperature: ");
            UART0_SendInteger(g_u8DriverSeatTemp);
            UART0_SendString(" C\r\n");
        }


        UART0_SendString("Driver Seat Heating Level: ");
        switch(g_ucDriverSeatState)
        {
        case 0:
            UART0_SendString("OFF\r\n");
            break;

        case 1:
            UART0_SendString("LOW\r\n");
            break;

        case 2:
            UART0_SendString("MED\r\n");
            break;

        case 3:
            UART0_SendString("HIGH\r\n");
            break;

        default:
            UART0_SendString("ERROR!!!\r\n");
            break;
        }

        UART0_SendString("Driver Seat Heater Intensity: ");
        switch(g_u8DriverSeatHeaterIntensity)
        {
        case 0:
            UART0_SendString("OFF\r\n");
            break;

        case 1:
            UART0_SendString("LOW\r\n");
            break;

        case 2:
            UART0_SendString("MED\r\n");
            break;

        case 3:
            UART0_SendString("HIGH\r\n");
            break;

        default:
            UART0_SendString("ERROR!!!\r\n");
            break;
        }


        /* ------------- Passenger Seat ------------- */

        if(g_u8PassengerSeatTemp > 40 || g_u8PassengerSeatTemp < 5)
        {
            UART0_SendString("Passenger Seat Temperature: ");
            UART0_SendString("ERROR!!!\r\n");
        }
        else
        {
            UART0_SendString("Passenger Seat Temperature: ");
            UART0_SendInteger(g_u8PassengerSeatTemp);
            UART0_SendString(" C\r\n");
        }


        UART0_SendString("Passenger Seat Heating Level: ");
        switch(g_ucPassengerSeatState)
        {
        case 0:
            UART0_SendString("OFF\r\n");
            break;

        case 1:
            UART0_SendString("LOW\r\n");
            break;

        case 2:
            UART0_SendString("MED\r\n");
            break;

        case 3:
            UART0_SendString("HIGH\r\n");
            break;

        default:
            UART0_SendString("ERROR!!!\r\n");
            break;
        }

        UART0_SendString("Passenger Seat Heater Intensity: ");
        switch(g_u8PassengerSeatHeaterIntensity)
        {
        case 0:
            UART0_SendString("OFF\r\n");
            break;

        case 1:
            UART0_SendString("LOW\r\n");
            break;

        case 2:
            UART0_SendString("MED\r\n");
            break;

        case 3:
            UART0_SendString("HIGH\r\n");
            break;

        default:
            UART0_SendString("ERROR!!!\r\n");
            break;
        }

    }

}


#if DEBUGGING_MODE_ACTIVATED == 1

void vRunTimeMeasurementsTask(void *pvParameters)
{

#if 0
    TickType_t xLastWakeTime = xTaskGetTickCount();
    static uint8 cRuntimeStatBuffer[ 1024 ];
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

#endif


    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        uint8 ucCounter, ucCPU_Load;
        uint32 ullTotalTasksTime = 0;
        vTaskDelayUntil(&xLastWakeTime, RUNTIME_MEASUREMENTS_TASK_PERIODICITY);
        for(ucCounter = 1; ucCounter < 14; ucCounter++)
        {
            ullTotalTasksTime += ullTasksTotalTime[ucCounter];
        }
        ucCPU_Load = (ullTotalTasksTime * 100) /  GPTM_WTimer0Read();

        taskENTER_CRITICAL();
        UART0_SendString("CPU Load is ");
        UART0_SendInteger(ucCPU_Load);
        UART0_SendString("% \r\n");
        taskEXIT_CRITICAL();
    }
}

#endif



