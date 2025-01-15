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

#ifndef __TASK_DINO_MOVE_H__
#define __TASK_DINO_MOVE_H__

#include "main.h"

extern TaskHandle_t Task_Handle_Dino_Move;

void task_dino_move(void *pvParameters);
void task_dino_move_init(void);

#endif