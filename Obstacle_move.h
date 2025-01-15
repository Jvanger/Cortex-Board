/**
 * @file task_dino_move.h
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TASK_OBSTACLE_MOVE_H__
#define __TASK_OBSTACLE_MOVE_H__

#include "main.h"
extern TaskHandle_t Task_Handle_Obstacle;
extern obstacle_x; 
 


void task_obstacle_move(void *pvParameters);
void task_obstacle_move_init(void);

#endif