/**
 * @file task_uart_receive.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TASK_UART_RECEIVE_LOGIC_H__
#define __TASK_UART_RECEIVE_H__

#include "main.h"

extern TaskHandle_t Task_Uart_Receive;
extern QueueHandle_t Queue_RX;

void task_uart_receive(void *pvParameters);
void task_uart_receive_init(void);

#endif