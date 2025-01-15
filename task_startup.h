/**
 * @file task_startup.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TASK_GAME_LOGIC_H__
#define __TASK_GAME_LOGIC_H__

#include "main.h"

extern TaskHandle_t Task_Handle_Startup;

void task_startup(void *pvParameters);
void task_startup_init(void);

#endif