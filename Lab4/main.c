/**
 * main.c
 */

#include <cyBot_uart.h>
#include <lcd.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PHJ Debug REMOVED #include "Timer.h"
#include <inc/tm4c123gh6pm.h>

// int main(void)
//{
//     timer_init(); // Initialize Timer, needed before any LCD screen functions
//     can be called
//                   // and enables time functions (e.g. timer_waitMillis)
//
//     lcd_init();   // Initialize the LCD screen.  This also clears the screen.
//     cyBot_uart_init();
//     cyBot_uart_init_last_half();  // Complete the UART device configuration
//
//     //cyBot_sendByte('A');
//
//     while (1)
//     {
//         char in = cyBot_getByte_blocking();
//
//         lcd_putc(in);
//     }
//
// }
