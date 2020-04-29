#include <REF_tm4c123gh6pm.h>
#include <stdbool.h>

//initialize the timer
void ping_init (void);

//activate the PING sensor
void ping_trigger(void);

//calculate distance
long ping_getDistance(long x,long y);
