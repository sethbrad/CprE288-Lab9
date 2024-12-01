/*
 *
 *   uart.c
 *
 *
 *
 *   @author
 *   @date
 */

#include "uart.h"
#include <stdint.h>

void uart_init(void) {
  // TODO
  // enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= 0x2;

  // enable clock to UART1
  SYSCTL_RCGCUART_R |= 0x02;

  // wait for GPIOB and UART1 peripherals to be ready
  //  while (SYSCTL_PRGPIO_R & 0b10 ) {};
  //  while (SYSCTL_PRUART_R & 0b10 ) {};

  // enable alternate functions on port B pins
  GPIO_PORTB_AFSEL_R |= 0x3;

  // enable digital functionality on port B pins
  GPIO_PORTB_DEN_R |= 0x3;

  // enable UART1 Rx and Tx on port B pins
  GPIO_PORTB_PCTL_R |= 0x11;

  // calculate baud rate
  //  uint16_t iBRD = 0x8; //use equations
  //  uint16_t fBRD = 0x2C; //   use equations FOR BAUD RATE OF 115200
  uint16_t iBRD = 0x68; // use equations
  uint16_t fBRD = 0xB;  //   use equations FOR BAUD RATE OF 9600

  // turn off UART1 while setting it up
  UART1_CTL_R &= 0xFFFFFFFE;

  // set baud rate
  // note: to take effect, there must be a write to LCRH after these assignments
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  // set frame, 8 data bits, 1 stop bit, no parity, no FIFO
  // note: this write to LCRH must be after the BRD assignments
  UART1_LCRH_R = 0b1100000;

  // use system clock as source
  // note from the datasheet UARTCCC register description:
  // field is 0 (system clock) by default on reset
  // Good to be explicit in your code
  UART1_CC_R = 0x0;

  // re-enable UART1 and also enable RX, TX (three bits)
  // note from the datasheet UARTCTL register description:
  // RX and TX are enabled by default on reset
  // Good to be explicit in your code
  UART1_CTL_R = 0x0301;
}

void uart_sendChar(char data) {
  // TODO
  while ((UART1_FR_R & 0x20) != 0)
    ;
  UART1_DR_R = data;
}

char uart_receive(void) {
  // TODO
  uint32_t ret;
  char rdata;

  while ((UART1_FR_R & 0x10) != 0)
    ;

  ret = UART1_DR_R;

  //    if(ret & 0xF00)
  //    {
  //        GPIO_PORTB_DR_R=0xF;
  //    }
  //    else
  //    {
  rdata = (char)(UART1_DR_R & 0xFF);
  //    }
  return rdata;
}

void uart_sendStr(const char *data) {
  // TODO for reference see lcd_puts from lcd.c file
  while (*data != '\0') {
    uart_sendChar(*data);
    data++;
  }
}
