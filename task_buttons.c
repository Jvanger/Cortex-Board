/**
 * @file task_buttons.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "task_buttons.h"

/*****************************************************************************/
/*  FreeRTOS Handles
/*****************************************************************************/
TaskHandle_t Task_Handle_SW1;
TaskHandle_t Task_Handle_SW2;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_SW1(void *pvParameters);
void task_SW1(void *pvParameters);
void task_buttons_init(void);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
events_t PROJ_ALERT_SW1 = EVENT_NONE;
events_t PROJ_ALERT_SW2 = EVENT_NONE;

void task_SW1(void *pvParameters) {

    // FOR SW1:
    bool sw1_prev = false;
    bool sw1_curr = false;

    while (1) {
        /* Sleep for 50mS -- DO NOT use any cyhal_ functions to delay */
        vTaskDelay(50);

        /* Check the current state of the button */
        if ((PORT_BUTTONS->IN & SW1_MASK) == 0x00) {
            sw1_curr = true;
        }
        else {
            sw1_curr = false;
        }

        /* Detect if the button has been pressed == Check the current and previous states of the button */
        if (sw1_curr && !sw1_prev) {
            PROJ_ALERT_SW1 = EVENT_SW1;
        }

        /* Update the previous button state */
        sw1_prev = sw1_curr;
    }
}

void task_SW2(void *pvParameters) {

    // FOR SW2:
    bool sw2_prev = false;
    bool sw2_curr = false;

    while (1) {
        /* Sleep for 50mS -- DO NOT use any cyhal_ functions to delay */
        vTaskDelay(50);

        /* Check the current state of the button */
        if ((PORT_BUTTONS->IN & SW2_MASK) == 0x00) {
            sw2_curr = true;
        }
        else {
            sw2_curr = false;
        }

        /* Detect if the button has been pressed == Check the current and previous states of the button */
        if (sw2_curr && !sw2_prev) {
            PROJ_ALERT_SW2 = EVENT_SW2;
        }

        /* Update the previous button state */
        sw2_prev = sw2_curr;
    }
}

void task_buttons_init(void) {

    xTaskCreate(
        task_SW1,
        "SW1 task",
        configMINIMAL_STACK_SIZE,
        NULL,
        4,
        &Task_Handle_SW1
    );

    xTaskCreate(
        task_SW2,
        "SW2 task",
        configMINIMAL_STACK_SIZE,
        NULL,
        4,
        &Task_Handle_SW2
    );    
}