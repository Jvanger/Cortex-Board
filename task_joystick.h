/**
 * @file task_joystick.h
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TASK_JOYSTICK_H__
#define __TASK_JOYSTICK_H__

#include "main.h"

extern TaskHandle_t Task_Handle_Joystick;
extern QueueHandle_t Queue_Joystick_Pos;

void task_joystick(void *pvParameters);
void task_joystick_init(void);

#endif