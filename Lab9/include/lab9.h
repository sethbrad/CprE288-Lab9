/*
 * lab9.h
 *
 *  Created on: Apr 29, 2020
 *      Author: Seth Braddock
 */

#ifndef LAB9_H_
#define LAB9_H_

int get_start_angle();
int get_stop_angle();
int get_object_distance();

// UART and GPIO initialization
void scan_init(void);

// formats data for putty
void send_to_putty(float data);

// reads from adc for IR distance
float ir_convert(void);

// sends string to Putty
void send_String(char str[]);

// cyBot_Scan and send data to Putty
void sensor_sweep(void);

// convert radius and angle data into arc distance
float convert_distance(float angle, float distance);

#endif /* LAB9_H_ */
