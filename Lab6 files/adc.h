#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
//Initializes the adc registers
void adc_init(void);

//Takes the samples and converts it
int adc_read(void);
