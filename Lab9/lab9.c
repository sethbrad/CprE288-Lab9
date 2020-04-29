#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "cybot_uart.h"

/*
 * lab9.c
 *
 *  Created on: Apr 29, 2020
 *      Author: Seth Braddock
 */

void sensor_sweep()
{
    cyBot_uart_init_clean(); // Clean UART initialization, before running your UART GPIO init code

    SYSCTL_RCGCGPIO_R |= 0b00000010; //system clock
    while ((SYSCTL_PRGPIO_R & 0b10) == 0)
    {
    };

    GPIO_PORTB_AFSEL_R |= 0x03; //select UART Rx and Tx
    GPIO_PORTB_PCTL_R &= 0xFFFFFF00;
    GPIO_PORTB_PCTL_R |= 0x00000011;

    GPIO_PORTB_DEN_R |= 0b00000011; //pin direction and digital enable
    GPIO_PORTB_DIR_R &= 0xFFFFFF00;
    GPIO_PORTB_DIR_R |= 0b00000010;

    cyBot_uart_init_last_half();  // Complete the UART device configuration
    cyBOT_init_Scan();

    /*
     while (1)
     {
     char in = cyBot_getByte_blocking();
     if (in == 'm')
     {
     break;
     }
     }
     */

    cyBOT_Scan_t scan;

    char header[] = "Angle\tPING Distance\tIR raw value";

    int j = 0;
    while (header[j] != '\0') //send header labels
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

        cyBot_sendByte('\t'); //Send ping value
        char val1[4];
        sprintf(val1, "%f", scan.sound_dist);

        while (val1[j] != '\0')
        {
            cyBot_sendByte(val1[j]);
            j++;
        }
        j = 0;

        cyBot_sendByte('\t');  //Send IR value
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

