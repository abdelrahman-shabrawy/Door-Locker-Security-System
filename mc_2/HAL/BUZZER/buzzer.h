/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Abdelrahman Shanrawy
 *
 *******************************************************************************/
#include "../../LIBRARIES/std_types.h"

#ifndef mc_2_HAL_BUZZER_BUZZER_H_
#define mc_2_HAL_BUZZER_BUZZER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Buzzer HW Ports and Pins Ids */
#define BUZZER_PORT_ID                 PORTA_ID
#define BUZZER_PIN_ID                  PIN2_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_init();
/*
 * Description :
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);
/*
 * Description :
 * Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);

#endif /* ℳC2_HAL_BUZZER_BUZZER_H_ */
