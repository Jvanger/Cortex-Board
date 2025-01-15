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

#ifndef __TASK_IMU_H__
#define __TASK_IMU_H__

#include "main.h"

extern TaskHandle_t Task_Handle_IMU;

void task_IMU(void *pvParameters);
void task_IMU_init(void);

#endif