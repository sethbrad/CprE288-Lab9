/*
 * ping_distance.h
 *
 *  Created on: Apr 29, 2020
 *      Author: Seth Braddock
 */

#ifndef PING_DISTANCE_H_
#define PING_DISTANCE_H_

void interruptHandler(void);

float ping_distance(void); // uses interrupts and timers to get PING distance

#endif /* PING_DISTANCE_H_ */
