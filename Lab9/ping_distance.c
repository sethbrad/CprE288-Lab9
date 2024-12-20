#include "Timer.h"
#include "driverlib/interrupt.h"
#include "lcd.h"
#include "ping.h"
#include <REF_tm4c123gh6pm.h>


// Global variables to store values from the IBR_R register
extern volatile long risingEdge;
extern volatile long fallingEdge;

volatile int counter = 0;
void interruptHandler(void);

/**
 * grabs ping distance val
 */
float ping_distance() {
  // makes sure to run the interrupt handler when one occurs in Timer 3B
  IntRegister(INT_TIMER3B, interruptHandler);

  // Enables interrupts for the system
  IntMasterEnable();

  // Configure NVIC for Timer3V
  NVIC_EN1_R |= 0x10;

  // set the priority of that bit to 3
  NVIC_PRI9_R |= 0xE0;

  // initialize the ultrasonic sensor
  ping_initi();

  ping_trig();
  float distance = ping_getDist(risingEdge, fallingEdge);

  return distance;
}

void interruptHandler() {
  // checks to see if an interrupt has occurred
  if ((TIMER3_MIS_R & 0x400) == 0x400) {
    if (counter % 2 == 0) {
      risingEdge = TIMER3_TBR_R;
      counter++;
    } else {
      fallingEdge = TIMER3_TBR_R;
      counter++;
    }
    // clears GPTM Timer B Capture Mode Event Interrupt
    TIMER3_ICR_R |= 0x400;
  }
}
