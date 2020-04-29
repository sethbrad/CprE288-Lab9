#include "Timer.h"
#include "lcd.h"
#include "ping.h"

/**
 * main.c
 */
int main(void)
{
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();

}
