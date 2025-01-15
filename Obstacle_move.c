/**
 * @file task_startup.c
 * @author your name 
 * @brief
 * @version 0.1
 * @date 2023-12-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Obstacle_move.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"
#include "task_game_logic.h"

/*****************************************************************************/
/*  FreeRTOS Handles
/*****************************************************************************/
TaskHandle_t Task_Handle_Obstacle_Move;
#define FONT_TIME_WIDTH     37 
#define FONT_TIME_HEIGHT    47 


/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_obstacle_move(void *pvParameters);
void task_obstacle_move_init(void);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
extern events_t PROJ_ALERT_SW1;
extern events_t PROJ_ALERT_SW2;
extern bool player1; 
extern Obs_Coordinates_t obs_pos;
extern Dino_Coordinates_t dino_pos;
extern Score_t score;


cyhal_gpio_callback_data_t sw2_callback_data;



/*****************************************************************************/
/* Interrupt Handlers                                                        */
/*****************************************************************************/
/* Interrupt handler callback function */
void sw2_handler(void *handler_arg, cyhal_gpio_event_t event)
{
    BaseType_t xHigherPriorityTaskWoken;

    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
     it will get set to pdTRUE inside the interrupt safe API function if a
     context switch is required. */
    xHigherPriorityTaskWoken = pdFALSE;

    /* Send a notification directly to the task to which interrupt processing
     * is being deferred.
     */
    vTaskNotifyGiveFromISR(Task_Handle_Obstacle_Move, &xHigherPriorityTaskWoken);

    /* Call the function that will force the task that was running prior to the
     * interrupt to yield*/
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*****************************************************************************/
/* Peripheral Initialization                                                 */
/*****************************************************************************/
void sw2_irq_enable(void)
{
    cyhal_gpio_init(PIN_SW2, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0);
    sw2_callback_data.callback = sw2_handler;
    cyhal_gpio_register_callback(PIN_SW2, &sw2_callback_data);
    cyhal_gpio_enable_event(PIN_SW2, CYHAL_GPIO_IRQ_FALL, 3, true);
}

void task_obstacle_move(void *pvParameters)
{
    bool temp = false;



    uint16_t notify = 0;
    // extern bool allow_Go = true;
    while (1)
    {
         int obstacle_x = 319;



        while (notify == 0)
        {
            vTaskDelay(40);
            notify = ulTaskNotifyTake(true, 10);
            if (notify != 0)
            {
               obs_pos.move = true;
                
            }
            
        }
        while (obs_pos.move)
        {

            if (abs(dino_pos.x - obs_pos.x) <= 10 && abs(dino_pos.y - obs_pos.y) <= 10)
            {
                if(score.curr_score > score.high_score) {
                    score.high_score = score.curr_score;
                }


                vTaskDelay(100);
                lcd_clear_screen(LCD_COLOR_BLACK);
                vTaskDelay(100); // wait for a second before displaying the game over screen
                lcd_O_wins();
                lcd_clear_screen(LCD_COLOR_BLACK);
                
                vTaskDelay(2000); 
                //display high score bit map on screen 
                if(score.high_score == 0){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score0_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 1){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score1_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 2){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score2_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 3){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score3_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 4){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score4_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 5){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score5_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 6){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score6_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 7){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score7_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 8){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score8_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else if(score.high_score == 9){
                    lcd_draw_image(CENTER_COL, CENTER_ROW, FONT_TIME_WIDTH, FONT_TIME_HEIGHT, Score9_Bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                
                    
                
                vTaskDelay(5000); // wait for 5 seconds before restarting the game
                

            }
            if (dino_pos.x >= obs_pos.x)
            {
                score.curr_score++;
                obs_pos.move = false;
                obs_pos.x = 319;
                notify = 0; 

                lcd_draw_image(obs_pos.x, obs_pos.y, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
              

                continue; 
                // obstacle should respawn from the screen end

            }

            lcd_draw_image(obstacle_x, 187, X_WIDTH, X_HEIGHT, Bitmaps_O, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            vTaskDelay(10);
            lcd_draw_image(obstacle_x, 187, X_WIDTH, X_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_BLACK);

            --obstacle_x;

            obs_pos.x = obstacle_x;
            obs_pos.y = 187;

        }
    }
}

void task_obstacle_move_init(void)
{

    sw2_irq_enable();

    xTaskCreate(
        task_obstacle_move,
        "Obstacle move",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Handle_Obstacle_Move);

}