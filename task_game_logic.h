/**
 * @file task_game_logic.h
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TASK_GAME_LOGIC_H__
#define __TASK_GAME_LOGIC_H__

#include "main.h"

extern TaskHandle_t Task_Handle_Game_Logic;
extern SemaphoreHandle_t Sem_Startup;
extern QueueHandle_t Queue_Dino_Pos;

typedef struct Dino_Coordinates_t{
    int x;
    int y;
} Dino_Coordinates_t;

typedef struct Obs_Coordinates_t{
    int x;
    int y;
    bool move; 
} Obs_Coordinates_t;

typedef struct IMU_P2{
    bool status;
    int value;
} IMU_P2;

typedef struct Score_t{
    int high_score;
    int curr_score;
} Score_t;


void task_game_logic(void *pvParameters);
void task_game_logic_init(void);

#endif