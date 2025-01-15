/**
 * @file task_game_logic.c
 * @author Saadan Surhyo (surhyo@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "task_game_logic.h"
#include "hw02.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"

/*****************************************************************************/
/*  FreeRTOS Handles
/*****************************************************************************/
TaskHandle_t Task_Handle_Game_Logic;
QueueHandle_t Queue_Dino_Pos;
extern QueueHandle_t Queue_RX;

// SemaphoreHandle_t Sem_Startup;
// extern SemaphoreHandle_t Sem_Startup_Done;

extern TaskHandle_t Task_Handle_Startup;
extern TaskHandle_t Task_Handle_Uart_Receive;
extern TaskHandle_t Task_Handle_Joystick;
extern TaskHandle_t Task_Handle_Dino_Move;
extern TaskHandle_t Task_Handle_SW2_Press;
#define FONT_TIME_WIDTH     37 
#define FONT_TIME_HEIGHT    47 

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_game_logic(void *pvParameters);
void task_game_logic_init(void);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
bool newgame, game_end;
bool jumped_over;

bool player1;
Dino_Coordinates_t dino_pos;
Obs_Coordinates_t obs_pos;
Score_t score;

IMU_P2 imu;
bool obs_active;

void task_game_logic(void *pvParameters)
{

    // variables:
    newgame = true;
    game_end = false;
    player1 = true;

    Queue_Dino_Pos = xQueueCreate(1, sizeof(Dino_Coordinates_t));

    int obs_delay = 30;
    obs_pos.x = 319;
    obs_pos.y = 185.5;
    imu.status = false;

    uint8_t dino_send[4];
    uint8_t dino_recieve[4];
    uint8_t obs_send[4];
    uint8_t obs_recieve[4];

    while (1)
    {

        if (!game_end)
        {


            if (newgame)
            {
                // prompt player 1 select screen
                lcd_select_player1();
                xTaskNotifyGive(Task_Handle_Startup);

                while (newgame)
                {
                    // xSemaphoreGive(Sem_Startup);
                    // wait for startup to be done:
                    // xSemaphoreTake(Sem_Startup_Done, portMAX_DELAY);
                    // newgame = false;
                }
            }

            // players selected, proceed to game now:

            if (player1)
            {

                // send notification to joystick to start detection
                xTaskNotifyGive(Task_Handle_Joystick);

                // send dino movement to player 2:
                // xQueueReceive(Queue_Dino_Pos, &dino_pos, 5);
                // dino_send[0] = (uint8_t) 'D';
                // dino_send[1] = (uint8_t) dino_pos.x;
                // dino_send[2] = (uint8_t) dino_pos.y;
                // dino_send[3] = '\n';
                // remote_uart_tx_string_polling(dino_send);

                // draw obstacle for p1:
                // lcd_draw_image(obs_pos.x, obs_pos.y, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                // xQueueReceive(Queue_RX, obs_recieve, 5);
                // CHECK IF ACTUALLY OBSTACLE !!!
                // obs_pos.x = (int) obs_recieve[1];
                // obs_pos.y = (int) obs_recieve[2];
                // lcd_draw_image(obs_pos.x, obs_pos.y, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
            }
            else
            {

                // obstacle stuff (send obstacle movement to player 1):

                // TODO: IMU READ - if active change delay to alter speed
                // TODO: send task notification to IMU to start detection
                if (imu.status)
                {
                }

                // if(obs_active) {
                //     lcd_draw_image(obs_pos.x, obs_pos.y, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                //     obs_pos.x = obs_pos.x + 1;
                //     vTaskDelay(obs_delay);
                //     lcd_draw_image(obs_pos.x, obs_pos.y, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                //     // green led to indicate active obs:
                //     PORT_RGB_RED->OUT_CLR = MASK_RGB_RED;
                //     PORT_RGB_GRN->OUT_SET = MASK_RGB_GRN;
                // }

                // send obstacle movement to player 1:
                // due queue thing
                // obs_send[0] = (uint8_t) 'O';
                // obs_send[1] = (uint8_t) obs_pos.x;
                // obs_send[2] = (uint8_t) obs_pos.y;
                // obs_send[3] = '\n';
                // remote_uart_tx_string_polling(obs_send);

                // dino draw for p2:
                // lcd_draw_image(dino_pos.x, dino_pos.y, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_WHITE, LCD_COLOR_BLACK);

                // xQueueReceive(Queue_RX, dino_recieve, 5);
                // CHECK IF ACTUALLY DINO !!!
                // dino_pos.x = (int) dino_recieve[1];
                // dino_pos.y = (int) dino_recieve[2];
                // // need to change:
                // //lcd_clear_screen(LCD_COLOR_BLACK);
                // //lcd_draw_rectangle_centered(SCREEN_CENTER_COL, 200, 319, 2, LCD_COLOR_WHITE);
                // lcd_draw_image(dino_pos.x, dino_pos.y, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
            }

            // FOR BOTH PLAYERS:

            // check for collision (P2/O wins):
            // if(dino_pos.x == obs_pos.x) {
            //     // suspend all other tasks?

            //     // check for high score:
            //     if(curr_score > high_score) {
            //         high_score = curr_score;
            //     }

            //     pwm_buzzer_start();
            //     vTaskDelay(100);
            //     pwm_buzzer_stop();
            //     // close all LEDS:
            //     PORT_RGB_GRN->OUT_CLR = MASK_RGB_GRN;
            //     PORT_RGB_RED->OUT_CLR = MASK_RGB_RED;
            //     lcd_clear_screen(LCD_COLOR_BLACK);
            //     lcd_O_wins();
            // }

            // check if dino jumped over the obstacle:
            // else if(dino_pos.x > obs_pos.x) {
            //     // increment p1 score:
            //     curr_score++;

            //     // make the obstacle disappear
            //     lcd_draw_image(obs_pos.x, obs_pos.y, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
            //     // obstacle should respawn from the screen end
            //     obs_pos.x = 319;
            //     obs_pos.y = 185.5;
            //     // should respawn on next sw2 press:
            //     obs_active = false;

            //     // red led to indicate non-active obs:
            //     PORT_RGB_GRN->OUT_CLR = MASK_RGB_GRN;
            //     PORT_RGB_RED->OUT_SET = MASK_RGB_RED;
            // }

            // check if P1/X wins:
            if (dino_pos.x >= 317)
            {

                game_end = true;

                // suspend all other tasks?
                vTaskSuspend(Task_Handle_Startup);
                vTaskSuspend(Task_Handle_Uart_Receive);
                vTaskSuspend(Task_Handle_Joystick);
                vTaskSuspend(Task_Handle_Dino_Move);
                // vTaskSuspend(Task_Handle_SW2_Press);

                // pwm_buzzer_start();
                // vTaskDelay(100);
                // pwm_buzzer_stop();
                // close all LEDS:
                PORT_RGB_GRN->OUT_CLR = MASK_RGB_GRN;
                PORT_RGB_RED->OUT_CLR = MASK_RGB_RED;
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                vTaskDelay(4000); 
             if(score.curr_score > score.high_score) {
                    score.high_score = score.curr_score;
                }
                
                lcd_clear_screen(LCD_COLOR_BLACK);
                
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
                
            
                vTaskDelay(5000);

                
            }

        }


    }

}

void task_game_logic_init(void)
{
    xTaskCreate(
        task_game_logic,
        "game logic",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Handle_Game_Logic);
}