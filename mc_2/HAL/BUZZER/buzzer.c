/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
 *
 * Author: Abdelrahman Shanrawy
 *
 *******************************************************************************/
#include "buzzer.h"
#include "../../LIBRARIES/common_macros.h"
#include "../../MCAL/GPIO/gpio.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function to enable the Buzzer through the GPIO.
 */

void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);

}

/*
 * Description :
 * Function to enable the Buzzer through the GPIO.
 */

void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}
/*
 * Description :
 * Function to disable the Buzzer through the GPIO.
 */

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

