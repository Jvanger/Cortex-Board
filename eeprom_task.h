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

#ifndef __TASK_EEPROM__H__
#define __TASK_EEPROM_MOVE_H__

#include "main.h"
extern TaskHandle_t Eeprom_Task_Handle;


void task_eeprom(void *pvParameters);
void task_eeprom_init(void);

#endif