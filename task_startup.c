/**
 * @file task_startup.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "task_startup.h"
#include "task_buttons.h"
#include "hw02.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"

/*****************************************************************************/
/*  FreeRTOS Handles
/*****************************************************************************/
TaskHandle_t Task_Handle_Startup;
extern TaskHandle_t Task_Handle_Uart_Receive;
extern QueueHandle_t Queue_RX;
// extern SemaphoreHandle_t Sem_Startup;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_startup(void *pvParameters);
void task_startup_init(void);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
extern events_t PROJ_ALERT_SW1;
extern events_t PROJ_ALERT_SW2;
extern bool player1;
extern bool newgame;
extern cyhal_uart_t cy_retarget_io_uart_obj;
cyhal_gpio_callback_data_t sw1_callback_data;

/*****************************************************************************/
/* Interrupt Handlers                                                        */
/*****************************************************************************/
/* Interrupt handler callback function */
void sw1_handler(void *handler_arg, cyhal_gpio_event_t event) {
    BaseType_t xHigherPriorityTaskWoken;

    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
     it will get set to pdTRUE inside the interrupt safe API function if a
     context switch is required. */
    xHigherPriorityTaskWoken = pdFALSE;

    /* Send a notification directly to the task to which interrupt processing
     * is being deferred.
     */
    vTaskNotifyGiveFromISR(Task_Handle_Startup, &xHigherPriorityTaskWoken);

    /* Call the function that will force the task that was running prior to the
     * interrupt to yield*/
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*****************************************************************************/
/* Peripheral Initialization                                                 */
/*****************************************************************************/
void sw1_irq_enable(void) {
    cyhal_gpio_init(PIN_SW1, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0);
    sw1_callback_data.callback = sw1_handler;
    cyhal_gpio_register_callback(PIN_SW1, &sw1_callback_data);
    cyhal_gpio_enable_event(PIN_SW1, CYHAL_GPIO_IRQ_FALL, 3, true);
}

void task_startup(void *pvParameters) {

    //printf("startup 00000\n");

    // changes made (moved out of infinte while loop):

    // wait for game_logic to start new game:
    // xSemaphoreTake(Sem_Startup, portMAX_DELAY);

    // main control wakes this up:
    ulTaskNotifyTake(true, portMAX_DELAY);

    uint8_t p2_receive[4];
    uint32_t notify = 0;

    while(1) {

        vTaskDelay(15);

        // only do this if there is a new game:
        if(newgame) {

            // only startup after sw1 has been pressed (Player 1 has been selected) 
            while(notify == 0) {



                // either button pressed:
                notify = ulTaskNotifyTake(true, 5);

                // or check if byte received from other player/board
                //xTaskNotifyGive(Task_Handle_Uart_Receive);
                xQueueReceive(Queue_RX, p2_receive, 5);
  

                if(p2_receive[0] == (uint8_t) MESSAGE_PLAYER1_SELECTION) {
                    printf("p2 received\n");
                    player1 = false;
                    break; // other player selected player 1                        
                }
            }    

            // if reached over here that means current SW2 was pressed by a player (Player 1 selection done)
            printf("PLAYER 1 SELECTED!!!\n");

            // draw dino-game:
            lcd_clear_screen(LCD_COLOR_BLACK);
            lcd_draw_image(24, 185.5, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            lcd_draw_rectangle_centered(SCREEN_CENTER_COL, 200, 319, 2, LCD_COLOR_WHITE);

            if(player1) {
                // send message over to p2 that sw1 has been pressed
                uint8_t p1_send[4];
                p1_send[0] = (uint8_t) MESSAGE_PLAYER1_SELECTION;
                p1_send[1] = '\n';
                remote_uart_tx_string_polling(p1_send);

                newgame = false;
                // startup finish:
                //xSemaphoreGive(Sem_Startup_Done);
            }
            else {
                newgame = false;
                // startup finish:
                //xSemaphoreGive(Sem_Startup_Done);
            }

            printf("STARTUP COMPLETE!!!\n");
        }
    }
}

void task_startup_init(void) {

    sw1_irq_enable();

    xTaskCreate(
        task_startup,
        "startup logic",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Handle_Startup
    );
}