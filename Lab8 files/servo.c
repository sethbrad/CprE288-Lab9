/*
 * servo.c
 *
 *  Created on: Apr 3, 2020
 *      Author: Seth Braddock
 */

#include "Timer.h"
#include "lcd.h"
#include <stdint.h>
#include "servo.h"

void servo_init()
{
    SYSCTL_RCGCGPIO_R |= 0x2; //Enables Clock for Port B

    GPIO_PORTB_DIR_R |= 0x20; //Set PB5 as output
    GPIO_PORTB_AFSEL_R |= 0x20; //Select Alternate Function on Port B pin 5
    GPIO_PORTB_PCTL_R |= 0x700000; //Disable Timers before configuring/Enable Alternate Function
    GPIO_PORTB_DEN_R |= 0x20; //Digital Enables for pin PB5

    TIMER1_CTL_R &= 0xEFF; //Disable timer B before editing
    TIMER1_CFG_R |= 0x4; //enable Timer 1B as 16-bit
    TIMER1_TBMR_R |= 0xA; //configure PWM for the timer
    TIMER1_CTL_R &= ~0x4000; //make non-inverting

    TIMER1_TBPR_R |= 0x4; //Set 8-bit prescaler
    TIMER1_TBILR_R &= ~0xFFFF;
    TIMER1_TBILR_R |= 0xE200;//Set the start value
    TIMER1_TBPMR_R |= 0x4; //Set 8-bit prescaler
    TIMER1_TBMATCHR_R |= 0x8440; //Set 8-bit match register
    TIMER1_CTL_R |= 0x100; //Re-enable timer B
}

int servo_move(float degrees)
{

    float high_time = ((degrees / 180) * 0.001) + 0.001;
    int low_time = 0.02 - high_time;
    int match_val = low_time * 16000000;

    int upper_part = match_val << 16; //grab the first two nibbles
    int lower_part = match_val & 0x00FFFF; //mask off the first two nibbles

    TIMER1_CTL_R &= 0xEFF; //Disable timer B before editing
    TIMER1_TBPMR_R &= ~0xFF;
    TIMER1_TBPMR_R |= upper_part; //Set prescale match val

    TIMER1_TBMATCHR_R &= ~0xFFFF;
    TIMER1_TBMATCHR_R |= lower_part; //Set match val

    TIMER1_CTL_R |= 0x100; //Start the timer

    return high_time;
}
