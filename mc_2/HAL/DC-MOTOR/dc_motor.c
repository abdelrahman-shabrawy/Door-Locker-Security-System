/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC_MOTOR driver
 *
 * Author: Abdelrahman Shabrawy
 *
 *******************************************************************************/
#include "dc_motor.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, PIN_OUTPUT);

	/* Motor is stop at the beginning */
	GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_LOW);
}

/*
 * Description:
 * The function responsible for rotate the DC Motor CW/
 * or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on
 * the required speed value
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* check the speed in range of 0 :100
	 * and convert it to duty cycle and send it to PWM driver
	 * */
	if((speed >= 0) && (speed <= 100))
	{
		PWM_Timer0_Start((uint8)(speed*2.55));
	}
	/* check the motor direction and set the pins as required in data sheet */
	switch (state)
	{
	case STOP :
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_LOW);
		break;
	case CW :

		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_LOW);
		break ;
	case A_CW :

		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_HIGH);
		break ;
	}

}

void PWM_Timer0_Start(uint8 duty_cycle)

{
	TCNT0 = 0; //Set Timer Initial value

	OCR0  = duty_cycle; // Set Compare Value

	//set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

