/**
 * @file task_collision.h
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _TASK_COLLISION_H_
#define _TASK_COLLISION_H_
#include "main.h"

extern TaskHandle_t Task_Handle_Collision_Check;

void task_collision(void *pvParameters);
void task_collision_init(void);




#endif 