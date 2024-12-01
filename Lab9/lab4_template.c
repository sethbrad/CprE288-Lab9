/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */

#include "lcd.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

#include "cyBot_uart.h" // Functions for communicating between CyBot and Putty (via UART1)
// PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h" // For scan sensors

// #define REPLACEME 0

/*
 int main(void)
 {
 button_init();
 timer_init(); // Must be called before lcd_init(), which uses timer functions
 lcd_init();

 // initialize the cyBot UART1 before trying to use it

 //(Uncomment ME for PuTTy to CyBot UART init part of lab)
 cyBot_uart_init_clean(); // Clean UART initialization, before running your UART
 GPIO init code

 // Complete this code for configuring the GPIO PORTB part of UART1
 initialization (your UART GPIO init code) SYSCTL_RCGCGPIO_R |= 0b00000010;
 //0b1 0000 while ((SYSCTL_PRGPIO_R & 0b10) == 0)
 {
 };

 GPIO_PORTB_AFSEL_R |= 0x03;
 GPIO_PORTB_PCTL_R &= 0xFFFFFF00;   // Force 0's in the desired locations
 GPIO_PORTB_PCTL_R |= 0x00000011;   // Force 1's in the desired locations
 //    Or see
 //    the notes
 //    for a coding alternative to assign a value to the PCTL field
 GPIO_PORTB_DEN_R |= 0b00000011;
 GPIO_PORTB_DIR_R &= 0xFFFFFF00;      // Force 0's in the desired locations
 GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the desired locations

 // (Uncomment ME for UART init part of lab)
 cyBot_uart_init_last_half();  // Complete the UART device configuration

 //    Initialze scan
 //    sensors
 cyBOT_init_Scan();

 // YOUR CODE HERE
 while (1)
 {
 char in = cyBot_getByte_blocking();
 if (in == 'm')
 {
 break;
 }
 }
 cyBOT_init_Scan();
 cyBOT_Scan_t scan;

 char header[] = "Angle\tPING Distance\tIR raw value";

 int j = 0;
 while (header[j] != '\0')
 {
 cyBot_sendByte(header[j]);
 j++;
 }
 j = 0;

 cyBot_sendByte('\n');
 cyBot_sendByte('\r');
 int i;
 for (i = 0; i < 185; i += 5)
 {
 //Scan and print i
 cyBOT_Scan(i, &scan);
 char val[4];
 sprintf(val, "%d", i);

 while (val[j] != '\0')
 {
 cyBot_sendByte(val[j]);
 j++;
 }
 j = 0;

 cyBot_sendByte('\t');
 //Send ping value
 char val1[4];
 sprintf(val1, "%f", scan.sound_dist);

 while (val1[j] != '\0')
 {
 cyBot_sendByte(val1[j]);
 j++;
 }
 j = 0;

 cyBot_sendByte('\t');
 //Send IR value
 char val2[4];
 sprintf(val2, "%d", scan.IR_raw_val);

 while (val2[j] != '\0')
 {
 cyBot_sendByte(val2[j]);
 j++;
 }
 j = 0;

 //Newline and return
 cyBot_sendByte('\n');
 cyBot_sendByte('\r');
 }
 }
 */
