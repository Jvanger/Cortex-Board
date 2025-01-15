 /**
 * @file task_light_sensor.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __TASK_LIGHT_SENSOR_H__
#define __TASK_LIGHT_SENSOR_H__

#include "main.h"

extern TaskHandle_t Task_Light_Handle;
extern QueueHandle_t Queue_Light_Status; 


#define LIGHT_THRESHOLD 11000
// I2C address of the LTR-329ALS-01
#define LTR_329ALS_01_ADDR 0x29 
// Define data register addresses
#define LTR_329ALS_01_DATA_CH1_LOW 0x88
#define LTR_329ALS_01_DATA_CH1_HIGH 0x89
#define LTR_329ALS_01_DATA_CH0_LOW 0x8A
#define LTR_329ALS_01_DATA_CH0_HIGH 0x8B

/**
 *
 *
 *
 */
void task_light_sensor_init(void);

/** Read the temperature from LTR_329ALS_01
 *
 * @param
 *
 */
float LTR_get_reading(void);

#endif /* __TASK_LIGHT_SENSOR_H__ */
