/**
 * @file task_uart_receive_logic.c
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "task_uart_receive.h"
#include "hw02.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"


/*****************************************************************************/
/*  FreeRTOS Handles
/*****************************************************************************/
TaskHandle_t Task_Handle_Uart_Receive;
QueueHandle_t Queue_RX;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_uart_receive(void *pvParameters);
void task_uart_receive_init(void);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
extern cyhal_uart_t cy_retarget_io_uart_obj;

void task_uart_receive(void *parameters) {

    Queue_RX = xQueueCreate(4, sizeof(uint8_t));
    uint8_t p2_recieve[4];

    while(1) {

        vTaskDelay(10);

        //ulTaskNotifyTake(true, portMAX_DELAY);

        if(remote_uart_rx_string_polling(p2_recieve)) {

            xQueueSend(Queue_RX, p2_recieve, portMAX_DELAY);
            printf("uart receive sent\n");

            // if(p2_recieve[0] == (uint8_t) MESSAGE_PLAYER1_SELECTION) {
            // }
            // else if( (p2_recieve[0] == (uint8_t) 'D')) {
            //     xQueueSend(Queue_RX, dino_rx, portMAX_DELAY);
            // }
            // else if( (p2_recieve[0] == (uint8_t) 'O')) {
            //     xQueueSend(Queue_RX, obs_rx, portMAX_DELAY);
            // }
        }
    }
}

void task_uart_receive_init(void) {
    xTaskCreate(
        task_uart_receive,
        "uart receive",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Handle_Uart_Receive
    );
}