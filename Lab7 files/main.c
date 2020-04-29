#include <REF_tm4c123gh6pm.h>
#include "Timer.h"
#include "lcd.h"
#include "ping.h"

//Global variables to store values from the IBR_R register
extern volatile long risingEdge;
extern volatile long fallingEdge;

volatile int counter = 0;
void interruptHandler(void);

/**
 * main.c
 */
int main(void)
{
    //makes sure to run the interrupt handler when one occurs in Timer 3B
    IntRegister (INT_TIMER3B,interruptHandler);

    //Enables interrupts for the system
    IntMasterEnable();

    //Configure NVIC for Timer3V
    NVIC_EN1_R |= 0x10;

    //set the priority of that bit to 3
    NVIC_PRI9_R |= 0xE0;

    //Always initialize the timer first
	timer_init();

	//Initialize the LCD function
	lcd_init();

	//initialize the ultrasonic sensor
    ping_init();

    while(1)
    {
        ping_trigger();
        long distance = ping_getDistance(risingEdge, fallingEdge);
        lcd_printf("%f cm",distance);
        timer_waitMillis(500);
    }
}

void interruptHandler()
{
    //checks to see if an interrupt has occurred
    if ((TIMER3_MIS_R & 0x400) == 0x400)
    {
        if (counter % 2 == 0)
        {
            risingEdge = TIMER3_TBR_R;
            counter++;
        }
        else
        {
            fallingEdge = TIMER3_TBR_R;
            counter++;
        }
        //clears GPTM Timer B Capture Mode Event Interrupt
        TIMER3_ICR_R |= 0x400;
    }
}

