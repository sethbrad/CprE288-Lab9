
#include "adc.h"
#include "lcd.h"
#include "movement.h"
#include "open_interface.h"
#include "timer.h"
#include "uart.h"
#include <math.h>

/**
 * main.c
 */
int main(void) {
  timer_init(); // must be called before lcd_init()
  lcd_init();
  uart_init();
  adc_init();
  char message[] = "Read      Voltage     Calculated\r\n";
  uart_sendStr(message);
  int measurements = 0;

  oi_t *sensor_data = oi_alloc();
  oi_init(sensor_data);
  int distance = 0;

  // For use during calibrations only
  //    while(distance<10){
  //        move_backwards(sensor_data, 1000);
  //        timer_waitMillis(1000);
  //        while(measurements<10)
  //            {
  //                timer_waitMillis(10000); // for initialization
  //                int count = 0;
  //                int read = 0;
  //                while (count<16)
  //                {
  //                    read += adc_read();
  //                    count++;
  //
  //                }
  //                //averages 16 read values
  //                read = read /16;
  //
  //                //multiply the voltage value by the digital value divided by
  //                its max digital value double numerator = 3.3 * read; double
  //                voltage = numerator / 4095; double length
  //                = 39.606*pow(voltage,-1.874);
  //
  //                char format[] = "";
  //                sprintf(format, "%d,      %.3f,      %.2f",
  //                read,voltage,length);
  //
  //                uart_sendStr(format);
  //                uart_sendChar('\r');
  //                uart_sendChar('\n');
  //                measurements++;
  //            }
  //    }
  //    oi_free(sensor_data); // do this once at end of main()
  //
  //
  while (measurements < 10) {
    timer_waitMillis(10000); // for initialization
    int count = 0;
    int read = 0;
    while (count < 16) {
      read += adc_read();
      count++;
    }
    // averages 16 read values
    read = read / 16;

    // multiply the voltage value by the digital value divided by its max
    // digital value
    double numerator = 3.3 * read;
    double voltage = numerator / 4095;
    double length = 39.606 * pow(voltage, -1.874);

    char format[] = "";
    sprintf(format, "%d,      %.3f,      %.2f", read, voltage, length);

    uart_sendStr(format);
    uart_sendChar('\r');
    uart_sendChar('\n');
    measurements++;
  }
  //    only for use once calibrated
  //    while(1)
  //    {
  //        timer_waitMillis(100); //for common use
  //        int count = 0;
  //        int read = 0;
  //        while (count<16)
  //        {
  //            read += adc_read();
  //            count++;
  //        }
  //        //averages 16 read values
  //        read = read /16;
  //        //multiply the voltage value by the digital value divided by its max
  //        digital value double numerator = 3.3 * read; double voltage =
  //        numerator / 4095; double calculation = 2754649 * pow(read,-1.57);
  //        //used power function in excel
  //
  //        lcd_printf("%.3f", calculation);
  //
  //        char format[] = "";
  //        sprintf(format, "%d,      %.3f,     %.1f",
  //        read,voltage,calculation);
  //
  //        uart_sendStr(format);
  //        uart_sendChar('\r');
  //        uart_sendChar('\n');
  //    }
}
