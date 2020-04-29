
#include <REF_tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>

void adc_init(void)
{
    //initialize the system clock
    SYSCTL_RCGCGPIO_R |= 0x2;

    //wait for the system clock to be ready
    while(SYSCTL_PRGPIO_R1 & 0x1 != 0x1)
    {
    }

    //make sure that the portB pins are initialized as inputs
    GPIO_PORTB_DIR_R &= ~0x10;
    //make sure the alternate function register is set for portB
    GPIO_PORTB_AFSEL_R |= 0x10;
    //make sure digital enable register is set to analog
    GPIO_PORTB_DEN_R &= ~0x10;
    //make sure the bnalog mode select register is set for port B
    GPIO_PORTB_AMSEL_R |= 0x10;
    //make sure the ADC system clock is started ton ADC0 (module 0)
    SYSCTL_RCGCADC_R |= 0x1;

    //wait for the ADC system clock to be ready
    while(SYSCTL_PRADC_R & 0x1 != 0x1)
    {
    }

    //Use sequencer 3 for the ASS
    ADC0_ACTSS_R &= ~0x08;
    //select the trigger for sequencer 3 as software
    ADC0_EMUX_R &= ~0xF000;

    ADC0_SSMUX3_R &= ~0x000F;
    //sets the analog input channel for sequencer 3
    ADC0_SSMUX3_R += 10;

    ADC0_SSCTL3_R = 0x0006;

    ADC0_ACTSS_R |= 0x08;
}
int adc_read(void)
{
    int result;
    //psi register is set to PB4
    ADC0_PSSI_R = 0x0008;
    //checks for interrupts
    while ((ADC0_RIS_R&0x08) == 0)
    {
    }
    result = ADC0_SSFIFO3_R&0xFFF;
    ADC0_ISC_R = 0x0008;
    return result;
}
