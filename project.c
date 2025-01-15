/**
 * @file project.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "project.h"
#include "task_game_logic.h"
#include "task_startup.h"
#include "task_uart_receive.h"
#include "task_joystick.h"
#include "task_dino_move.h"
//#include "task_sw2_press.h"

char ICE_DESCRIPTION[] = "";

/**
 * @brief 
 * This function will initialize all of the hardware resources for
 * the ICE.  
 */
void peripheral_init(void) {

    /* Initialize the RGB LEDs */
    leds_init();
    /* Initialize the buttons */
    push_buttons_init();
    /* Initialize the Buzzer */
    pwm_buzzer_init();
    /* Initialize the LCD */
    ece353_enable_lcd();
    /* Initialize the joystick*/
    joystick_init();

    /* Initialize the remote UART */
    remote_uart_init();
    remote_uart_enable_interrupts();

    /* Initialize the i2C bus */
    i2c_init();

    /* Initialize Timer to generate interrupts every 100mS*/
    // timer_init(&hw02_timer_obj, &hw02_timer_cfg, 10000000, Handler_Timer);
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief 
 * This function implements the behavioral requirements for the ICE
 * 
 * This function is implemented in the iceXX.c file for the ICE you are 
 * working on.
 */
void main_app(void) {
    
    task_game_logic_init();
    task_startup_init();
    task_uart_receive_init();
    task_joystick_init();
    task_dino_move_init();
    task_obstacle_move_init();
    //task_sw2_press_init();
    // task_buttons_init();
   // task_eeprom_init(); 
 //  task_light_sensor_init();
    vTaskStartScheduler();
    

    while (1) {};
}