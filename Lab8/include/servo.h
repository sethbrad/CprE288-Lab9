/*
 * servo.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Seth Braddock
 */

#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>

#ifndef SERVO_H_
#define SERVO_H_

// initialize the servo motor
void servo_init(void);

// make the servo move n degrees
int servo_move(float degrees);

#endif /* SERVO_H_ */
