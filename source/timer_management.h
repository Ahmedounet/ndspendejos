/*
 * timer_management.h
 *
 *  Created on: Jan 5, 2020
 *      Author: nds
 */

#ifndef TIMER_MANAGEMENT_H_
#define TIMER_MANAGEMENT_H_



#include <nds.h>

void initTimer();

void timerISR();

void reset_timer();



#endif /* TIMER_MANAGEMENT_H_ */
