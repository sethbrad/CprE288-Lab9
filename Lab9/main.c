#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "cybot_uart.h"
#include "lab9.c"

/**
 * main.c
 */
int main(void)
{

    timer_init();
    lcd_init();

    //sweep sensors and displays on Putty
    sensor_sweep();

    //use IR for arc length and PING for distance
    //identify objects

    //point servo at object

    //convert to linear width
}
