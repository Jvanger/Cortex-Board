/**
 * @file task_joystick.c
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "task_joystick.h"
#include "project.h"

/*****************************************************************************/
/*  FreeRTOS Handles
/*****************************************************************************/
TaskHandle_t Task_Handle_Joystick;
QueueHandle_t Queue_Joystick_Pos;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_joystick(void *pvParameters);
void task_joystick_init(void);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/


/**
 * @brief 
 * This function will monitor the current position of the joystick. 
 * @param pvParameters 
 */
void task_joystick(void *pvParameters) {

    /* Allocate any (local or else) variables used in this task */
    joystick_position_t cur_pos = JOYSTICK_POS_CENTER;
    joystick_position_t prev_pos = JOYSTICK_POS_CENTER;
    Queue_Joystick_Pos = xQueueCreate(1, sizeof(joystick_position_t));

    // wait until game begins, game_logic will send a task notification
    ulTaskNotifyTake(true, portMAX_DELAY);

    while (1) {
        vTaskDelay(20);

        cur_pos = joystick_get_pos();

        // Check to see what the current position of the joystick is. 
        if ((cur_pos != JOYSTICK_POS_CENTER) && (cur_pos != prev_pos)) // confrim this with team cuz not really essential, 
        // can just have something else that does this, not neccasrily a task needed for this
        {
            /* Send the current joystick position to the joystick position queue */
            xQueueSend(Queue_Joystick_Pos, &cur_pos, portMAX_DELAY);
        }
        prev_pos = cur_pos;
    }
}

void task_joystick_init(void) {
    xTaskCreate(
        task_joystick,
        "joystick task",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Handle_Joystick
    );
}