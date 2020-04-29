#include "button.h"
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

    button_init();
    timer_init();
    lcd_init();

    //sweep sensors
    sensor_sweep();

    //send data to Putty

    //identify objects

    //convert to linear width
}
