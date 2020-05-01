/**
 * main.c
 */

#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "Timer.h"
#include "lcd.h"
#include <stdint.h>
#include "servo.h"

int main(void)
{
    timer_init();
    servo_init();

    servo_move(90);//Moves the servo
    delay(10000); //This holds the position

    servo_move(30);
    delay(10000);

    servo_move(150);
    delay(10000);

    servo_move(90);
    delay(10000);
}
