/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC_MOTOR driver
 *
 * Author: Abdelrahman Shabrawy
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include <avr/io.h>
#include "../../LIBRARIES/std_types.h"
/* INCLUDE MICROCONTROLLER ABSTRCTION LAYERS WHICH IS GPIO */
#include "../../MCAL/GPIO/gpio.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum
{
	STOP,CW,A_CW
}DcMotor_State;

/* DC_MOTOR HW Ports and Pins Ids */
#define DC_MOTOR_OPUT_PORT_ID                   PORTA_ID
#define DC_MOTOR_OPUT_A_PIN_ID                  PIN5_ID
#define DC_MOTOR_OPUT_B_PIN_ID                  PIN6_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);

/*
 * Description:
 * The function responsible for rotate the DC Motor CW/
 * or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on
 * the required speed value
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* DC_MOTOR_H_ */
