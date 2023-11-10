/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the TIMER driver
 *
 * Author: Abdelrahman Shanrawy
 *
 *******************************************************************************/
//Timer1_ConfigType Timer_Configrations = {0,250,EIGHT_PRESCALER,COMPARE};

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include "../../LIBRARIES/std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	OVERFLOW,COMPARE
}Timer1_Mode;

typedef enum
{
	NO_CLOCK,NO_PRESCALE,F_CPU_8 ,F_CPU_64,F_CPU_256,F_CPU_1024
}Prescaler;

typedef struct
{
	Timer1_Mode mode;
	uint16 timer1_initialvalue;
	uint16 timer1_comparevalue;
	Prescaler timer1_prescaler;
}Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Functional responsible for Initialize the TIMER_1 driver by:
 * 1. Setup the initial value for the timer
 * 2. Adjusting the TIMER_1 registers for the required mode and prescaler
 * 3. Enabling the interrupt
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);


void Timer1_setCallBack(void(*a_ptr)(void));

/*
 * Description :
 * Function responsible to stop the timer */
void Timer1_stop();

/*
 * Description :
 * Function responsible to shut down the timer by clearing all the registers of the module */
void Timer1_deinit(void);


#endif /* MCAL_TIMER_TIMER_H_ */
