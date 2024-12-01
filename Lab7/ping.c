#include "Timer.h"
#include <REF_tm4c123gh6pm.h>
#include <stdbool.h>


// Global variables to store values from the IBR_R register
extern volatile long risingEdge;
extern volatile long fallingEdge;

// Stores the total distance
float distance;
// keeps track of the number of overflows
int numOverflow;
// keeps track of the total clock cycles
long totalClockCycles;

// initialize the timer
void ping_init(void) {
  // enable clock for Timer 3
  SYSCTL_RCGCTIMER_R = 0x8;

  // wait for peripheral timer to activate
  while ((SYSCTL_PRTIMER_R & 0x8) == 0) {
  };

  // Enable alternate function on portB pin 3
  GPIO_PORTB_AFSEL_R |= 0x8;

  // enable alternate function for timerB on pb3
  GPIO_PORTB_PCTL_R |= 0x7000;

  // Disable the timer b enable bit
  TIMER3_CTL_R &= 0xFEFF;

  // Configure to use specific timer (Timer 3 set to 16 bit counter)
  TIMER3_CFG_R |= 0x00000004;

  // set the register to edge-time mode, capture mode, and count down mode;
  TIMER3_TBMR_R |= 0x7;

  // Configure the event for both positive and negative edges on timer 3B
  TIMER3_CTL_R |= 0xC00;

  // Sets the prescaler to to extend to 24 bits (With maximum value since we are
  // counting down)
  TIMER3_TBPR_R |= 0xFF;

  // Sets the 16-bit timer with a maximum loaded value (Because we are counting
  // down)
  TIMER3_TBILR_R |= 0xFFFF;

  // Enables interupts for Timer B
  TIMER3_IMR_R |= 0x800;

  // enables the timer and starts counting
  TIMER3_CTL_R |= 0x100;

  // Clear the status flags
  TIMER3_ICR_R |= 0x400;
}

// activate the PING sensor
void ping_trigger(void) {
  // enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= 0b00000010;

  // wait for the system clock to activate
  while ((SYSCTL_PRGPIO_R & 0b10) == 0) {
  };

  // Digitally enable pb3
  GPIO_PORTB_DEN_R = 0b1000;

  // Disable alternate function on portB pin 3
  GPIO_PORTB_AFSEL_R &= 0x00;

  // disable timer 3B
  GPIO_PORTB_PCTL_R &= 0x0000;
  //
  //    //enable alternate function for timerB on pb3
  //    GPIO_PORTB_PCTL_R |= 0x7000;

  // Disables Interrupts
  TIMER3_IMR_R && 0x0;

  // initialize pin pb3 as an output
  GPIO_PORTB_DIR_R |= 0b1000;

  // Turn on sensor and send pulse;
  GPIO_PORTB_DATA_R |= 0b0000;

  GPIO_PORTB_DATA_R |= 0b1000;
  // Wait 5 microseconds on the high signal so it registers the high
  timer_waitMicros(5);

  GPIO_PORTB_DATA_R |= 0b0000;

  // Re-enable Alternate function direction should automatically be set back to
  // an input
  GPIO_PORTB_AFSEL_R |= 0x8;

  // Clears ICR Register
  TIMER3_ICR_R |= 0x400;

  // Enables interupts for Timer B
  TIMER3_IMR_R |= 0x800;

  //    //Read from Timer3_TBR_R for the initial timer
  //    risingEdge = TIMER3_TBR_R;

  //    //Read from Timer3_TBR_R for the falling edge of the timer
  //    fallingEdge = Timer3_TBR_R;
}

// calculate distance
long ping_getDistance(long start, long stop) {
  risingEdge = start;
  fallingEdge = stop;
  // This would be a case of overflow
  if (risingEdge - fallingEdge < 0) {
    numOverflow++;
    totalClockCycles = -1 * (risingEdge - fallingEdge);
  }
  // Convert clock cycle to time
  else {
    totalClockCycles = risingEdge - fallingEdge;
  }

  // 16 x 10^6 -----> 1 sec
  // totalClockCycles/16*10^6 = time in seconds
  long time = totalClockCycles / (16 * 10 * 10 * 10 * 10 * 10 * 10);

  // calculate distance by converting to centimeters
  distance = 34300 * time;
  // divide by two because of round trip
  distance = distance / 2;

  return distance;
}
