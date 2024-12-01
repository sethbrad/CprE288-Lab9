#include <REF_tm4c123gh6pm.h>
#include <stdbool.h>

// initialize the timer
void ping_initi(void);

// activate the PING sensor
void ping_trig(void);

// calculate distance
long ping_getDist(long x, long y);
