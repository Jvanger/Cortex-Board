 /**
 * @file task_light_sensor.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
 
 #include "task_light_sensor.h"

 TaskHandle_t Task_Light_Handle = NULL;
 QueueHandle_t Queue_Light_Status;


/** Read a register on the LTR_329ALS_01
 *
 * @param reg The reg address to read
 *
 */
static uint16_t LTR_read_reg(uint8_t reg_low, uint8_t reg_high) {
    cy_rslt_t rslt;
    uint8_t write_data[1];
    uint8_t read_data[1];
    uint16_t return_value;

    // Read the low byte
    write_data[0] = reg_low;
    rslt = cyhal_i2c_master_write(&i2c_monarch_obj, LTR_329ALS_01_ADDR, write_data, 1, 0, true);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the write failed, halt the CPU

    rslt = cyhal_i2c_master_read(&i2c_monarch_obj, LTR_329ALS_01_ADDR, read_data, 1, 0, true);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the read failed, halt the CPU
    uint8_t data_low = read_data[0];

    // Read the high byte
    write_data[0] = reg_high;
    rslt = cyhal_i2c_master_write(&i2c_monarch_obj, LTR_329ALS_01_ADDR, write_data, 1, 0, true);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the write failed, halt the CPU

    rslt = cyhal_i2c_master_read(&i2c_monarch_obj, LTR_329ALS_01_ADDR, read_data, 1, 0, true);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the read failed, halt the CPU
    uint8_t data_high = read_data[0];

    // Combine the low and high bytes
    return_value = ((uint16_t)data_high << 8) | data_low;

    return return_value;
}

/** Read the value of the input port
 *
 * @param reg The reg address to read
 *
 */
float LTR_get_reading(void)
{
    uint16_t ALS_CH1_ADC_Data = LTR_read_reg(LTR_329ALS_01_DATA_CH1_LOW, LTR_329ALS_01_DATA_CH1_HIGH); // Read ALS_DATA_CH1
    vTaskDelay(80);
    uint16_t ALS_CH0_ADC_Data = LTR_read_reg(LTR_329ALS_01_DATA_CH0_LOW, LTR_329ALS_01_DATA_CH0_HIGH); // Read ALS_DATA_CH0
    vTaskDelay(80);
	//int16_t raw_value = LTR_read_reg(LTR_TEMP_REG);
	float temp = (double)ALS_CH0_ADC_Data / 2;
    printf("Light Sensor Reading: %f\n", temp);
	return temp;
}


void task_light_sensor(void *pvParameters)
{
    bool threshold_crossed;
    if (LTR_get_reading() >= LIGHT_THRESHOLD) {
        threshold_crossed = true;
    }
    else {
        threshold_crossed = false;
    }

    // Detect light intensity
    while (1)
    {
        vTaskDelay(50);
        if (threshold_crossed && LTR_get_reading() >= LIGHT_THRESHOLD) {
            ;
        }
        else if (!threshold_crossed && LTR_get_reading() < LIGHT_THRESHOLD) {
            ;
        }
        else {
            //send new light status to queue
            xQueueSend(Queue_Light_Status, &threshold_crossed, portMAX_DELAY);
            threshold_crossed = !threshold_crossed;
        }

        // Delay for 10mS using vTaskDelay
        vTaskDelay((50));
    }

}

void task_light_sensor_init(void) {
    Queue_Light_Status = xQueueCreate(1, sizeof(bool));

    xTaskCreate(
        task_light_sensor, 
        "Task Light Sensor", 
        configMINIMAL_STACK_SIZE, 
        NULL, 
        3, 
        &Task_Light_Handle
    );
}

