/**
 * @file task_dino_move.c
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "task_dino_move.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"
#include "task_game_logic.h"

/*****************************************************************************/
/*  FreeRTOS Handles
/*****************************************************************************/
TaskHandle_t Task_Handle_Dino_Move;
extern QueueHandle_t Queue_Joystick_Pos;
extern QueueHandle_t Queue_Dino_Pos;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_dino_move(void *pvParameters);
void task_dino_move_init(void);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
extern Dino_Coordinates_t dino_pos;
extern Dino_Coordinates_t obs_pos;

/**
 * @brief
 * This function will monitor the current position of the joystick.
 * @param pvParameters
 */
void task_dino_move(void *pvParameters)
{

    /* Allocate any (local or else) variables used in this task */
    bool onGround = false;
    bool dir_up;
    bool dir_right;
    int y = 185.5;
    int x = 24;

    BaseType_t joystick_status;
    joystick_position_t pos;

    while (1)
    {

        vTaskDelay(10);

        // Receive the current position of the joystick from the Queue, timeout after 5mS.
        joystick_status = xQueueReceive(Queue_Joystick_Pos, &pos, 5); // next time if didn't receive so fail status??

        /* Check to see if a valid message was received */
        if (joystick_status == pdPASS)
        {

            /* Based on the information received, determine whether the dino should jump */
            /* This implementation does NOT support diagonal movements*/
            switch (pos)
            {

            case JOYSTICK_POS_UP:
            case JOYSTICK_POS_UPPER_LEFT:
            case JOYSTICK_POS_UPPER_RIGHT:
            {
                onGround = false;
                dir_up = true;

                // jump until dino back to ground
                printf("dino jump\n");
                while (!onGround)
                {

                    dino_pos.x = x;
                    dino_pos.y = y;
                    /* Send the current dino position to the dino queue */
                    // xQueueSend(Queue_Dino_Pos, &dino, 5);

                    vTaskDelay(3);

                    if (dir_up)
                    {

                      
                        if (y > 120)
                        {
                            --y;
                        }
                        else
                        {
                            dir_up = false;
                        }
                    }
                    else
                    {


                        if (y < 185.5)
                        {
                            ++y;
                        }
                        else
                        {
                            dir_up = true;
                            onGround = true; // reached back to ground
                        }
                    }

                    lcd_draw_image(x, y, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                    vTaskDelay(15); 
                    lcd_draw_image(x, y, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                }

                break;
            }

            case JOYSTICK_POS_RIGHT:
            case JOYSTICK_POS_LOWER_RIGHT:
            {
                lcd_draw_image(x, y, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                x = x + 10;
                lcd_draw_image(x, y, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_WHITE, LCD_COLOR_BLACK);

                dino_pos.x = x;
                dino_pos.y = y;

                /* Send the current dino position to the dino queue */
                // xQueueSend(Queue_Dino_Pos, &dino, 5);

                break;
            }


            case JOYSTICK_POS_LOWER_LEFT:
            case JOYSTICK_POS_DOWN:
            {
                lcd_draw_image(x, y, X_WIDTH, X_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                dino_pos.y = dino_pos.y + 5;  
                lcd_draw_image(x, y, X_WIDTH, X_HEIGHT, Bitmaps_O, LCD_COLOR_WHITE, LCD_COLOR_BLACK);

                dino_pos.x = x;
                dino_pos.y = y;
                break; 
            }


            }
        }
    }
}

void task_dino_move_init(void)
{
    xTaskCreate(
        task_dino_move,
        "Dino move",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Handle_Dino_Move);
}