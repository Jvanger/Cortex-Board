#include "eeprom_task.h"
#include "main.h" 
#include "task_game_logic.h"
#include "Obstacle_move.h"

TaskHandle_t Eeprom_Task_Handle; 
extern Score_t score; 

void task_eeprom(void *pvParameters);
void task_eeprom_init(void);


void task_eeprom(void *pvParameters) {

    uint16_t high_score_address = 0x03; 
    
    while(1) {

        // Save high score 
        eeprom_write_byte(high_score_address, score.high_score);

        // Add delay 
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_eeprom_init(void) {
    eeprom_read_byte(0x03);

    // Start task
    xTaskCreate(
        task_eeprom,
        "eeprom task",
        configMINIMAL_STACK_SIZE, 
        NULL,
        1,
        &Eeprom_Task_Handle
    );
}