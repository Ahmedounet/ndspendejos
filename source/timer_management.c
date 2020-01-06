/*
 * timer_management.c
 *
 *  Created on: Jan 5, 2020
 *      Author: nds
 */

#include "timer_management.h"
#include "gameplay_main.h"
#include "gameplay_sub.h"

int timer_ticks;

void initTimer() {
	// Initialize timer_ticks
	timer_ticks = 0;

	TIMER1_CR= TIMER_ENABLE | TIMER_DIV_1024 |TIMER_IRQ_REQ;
	// Configure timer to trigger an interrupt every 100 ms

	TIMER1_DATA= TIMER_FREQ_1024(10);

	// Associate the ISR (timerISR) to the interrupt line and enable it
	irqSet(IRQ_TIMER1 , &timerISR);
	irqEnable(IRQ_TIMER1);

}

void timerISR() {

	timer_ticks++;

	if( timer_ticks>=100)
	{
		timer_ticks=0;
		if(!priorities[HOME_SCREEN])
		{
			irqDisable(IRQ_TIMER1);

			losing_screen(FROM_HOME);
		}
	}

}

void reset_timer()
{
	timer_ticks=0;
}
