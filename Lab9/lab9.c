#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "cybot_uart.h"
#include "ping.h"
#include "ping_distance.h"
#include "stdbool.h"

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

    int temp = 0; //temp for comparing IR values
    int current = 0;

    int start_angle = 0;
    int stop_angle = 0;

    int i;
    for (i = 0; i <= 180; i += 5)
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

        //
        //

        float radius = ping_distance();

        bool object_detected = false;

        //
        //

        cyBot_sendByte('\t'); //Send ping value
        char val1[4];
        sprintf(val1, "%f", radius);

        while (val1[j] != '\0')
        {
            cyBot_sendByte(val1[j]);
            j++;
        }
        j = 0;

        cyBot_sendByte('\t');  //Send IR value
        char val2[4];
        sprintf(val2, "%d", scan.IR_raw_val);

        //
        //
        //

        //compare current to temp
        if (i == 0)
        {
            current = radius;

        }
        else
        {
            temp = current;
            current = radius;
        }

        if (current - temp >= 10 || current - temp <= -10) { //10 cm threshold value
            if (!object_detected) {
                object_detected = true;
                start_angle = i;
            } else {
                object_detected = false;
                stop_angle = i;
            }
        }

        //
        //
        //

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

float convert_distance(float angle, float radius)
{
    float angle_rad = (angle / 180) * 3.14;

    float linear_distance = angle_rad * radius;

    return linear_distance;
}

