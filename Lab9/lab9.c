#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "cybot_uart.h"
#include "ping.h"
#include "ping_distance.h"
#include "stdbool.h"

int start_angle = 0;
int stop_angle = 0;
int object_distance = 0;
/*
 * lab9.c
 *
 *  Created on: Apr 29, 2020
 *      Author: Seth Braddock
 */

int get_start_angle()
{
    return start_angle;
}
int get_stop_angle()
{
    return stop_angle;
}
int get_object_distance()
{
    return object_distance;
}

void scan_init()
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

}
void sensor_sweep()
{
    cyBOT_Scan_t scan; //scan struct

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

    //
    //

    int temp = 0; //temp for comparing IR values
    int current = 0;

    int i;
    for (i = 0; i <= 180; i += 2)
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

        // CALLS PING DISTANCE TO DISPLAY ON LCD
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

        //
        //

        //
        //

        cyBot_sendByte('\t');  //Send IR value
        char val2[4];
        sprintf(val2, "%d", scan.IR_raw_val);

        //
        // CHECKS TO UPDATE IF OBJECT THRESHOLD PRESENT

        if (i == 0) //compare current to temp
        {
            current = radius;

        }
        else
        {
            temp = current;
            current = radius;
        }

        if (current - temp >= 10 || current - temp <= -10)
        {
            if (!object_detected) //10 cm threshold value
            {
                object_detected = true;
                start_angle = i;
                object_distance = radius;
            }
            else
            {
                object_detected = false;
                stop_angle = i;
            }
        }

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

