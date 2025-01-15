/**
 * @file task_buttons.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TASK_BUTTONS_H__
#define __TASK_BUTTONS_H__

#include "main.h"
#include "hw02.h"

extern events_t PROJ_ALERT_SW1;
extern events_t PROJ_ALERT_SW2;

extern TaskHandle_t Task_Handle_SW1;
extern TaskHandle_t Task_Handle_SW2;

void task_SW1(void *pvParameters);
void task_SW1(void *pvParameters);
void task_buttons_init(void);

#endif