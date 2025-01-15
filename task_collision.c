

//#include "task_collision.h"
#include "main.h" 
#include "task_dino_move.h"
#include "Obstacle_move.h"


TaskHandle_t Task_Handle_Collision_Check; 
/**
 * Function Declarations
 */
void task_collision(void *pvParameters); 
void task_collision_init(void);
// int dinosaur_x; 
// int dinosaur_y;
// int obstacle_x;

void check_collision(void *pvParameters) {
    

//   if (dinosaur_x == obstacle_x && dinosaur_y >= 150) {
//     // Collision detected 
//     lcd_X_wins(); 
//   }

}

// Call check_collision() periodically 
void task_collision_init(void) {


  xTaskCreate(check_collision, "Collision", configMINIMAL_STACK_SIZE, NULL, 1, &Task_Handle_Collision_Check);

}