#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "cybot_uart.h"
#include "lab9.h"

/**
 * main.c
 */
int main(void)
{

    timer_init();
    lcd_init();
    servo_init();
    adc_init();

    //sweep sensors and displays on Putty
    scan_init();
    sensor_sweep();

    //use IR for arc length and PING for distance
    //identify objects
    int angle_spread = get_stop_angle() - get_start_angle();
    int result;

    //point servo at object

    servo_init();
    servo_move((get_start_angle() + angle_spread) / 2);

    //convert to linear width
    result = convert_distance(angle_spread, get_object_distance());

    lcd_printf("Object is &d cm away from cyBOT", result);
}
