/*
 * lab9.h
 *
 *  Created on: Apr 29, 2020
 *      Author: Seth Braddock
 */

#ifndef LAB9_H_
#define LAB9_H_

//cyBot_Scan and send data to Putty
void sensor_sweep(void);

//convert radius and angle data into arc distance
float convert_distance(float angle, float distance);

#endif /* LAB9_H_ */
