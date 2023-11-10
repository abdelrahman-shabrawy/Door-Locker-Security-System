/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the TIMER driver
 *
 * Author: Abdelrahman Shanrawy
 *
 *******************************************************************************/
#include "timer.h"
#include <avr/io.h> /* To use the UART Registers */
#include <avr/interrupt.h>
#include "../../LIBRARIES/common_macros.h" /* To use the macros like SET_BIT */
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/* Interrupt Service Routine for timer1 overflow mode */

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* Interrupt Service Routine for timer1 compare mode */

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the TIMER_1 driver by:
 * 1. Setup the initial value for the timer
 * 2. Adjusting the TIMER_1 registers for the required mode and prescaler
 * 3. Enabling the interrupt
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1 = (Config_Ptr->timer1_initialvalue) & 0XFFFF; /* set initial value */
	TCCR1A =0;
	TCCR1B =0;
	TCCR1B = (TCCR1B  & 0XF8) | (Config_Ptr->timer1_prescaler); /* set the prescaler */
	switch(Config_Ptr->mode)
	{
	case OVERFLOW:
		TCCR1A |= (1<<FOC1A); /* Adjust for overflow mode */
		TIMSK |= (1<<TOIE1); /* Enable Timer1 Compare A Interrupt */
		break;
	case COMPARE:
		OCR1A = (Config_Ptr->timer1_comparevalue)& 0XFFFF; // Set Compare Value
		TCCR1A |= (1<<FOC1A) | (1<<WGM01); /* Adjust for compare mode */
		TCCR1B |= (1<<WGM12);
		TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */
		break;
	}
}


void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

/*
 * Description :
 * Function responsible to stop the timer */

void Timer1_stop(void)
{
	TCCR1B = (TCCR1B & 0XF8);
}

/*
 * Description :
 * Function responsible to shut down the timer by clearing all the registers of the module */

void Timer1_deinit(void)
{
	TCCR1A= 0;
	TCCR1B=0;
	TCNT1= 0;
	OCR1A= 0;
	TIMSK= 0;
}
