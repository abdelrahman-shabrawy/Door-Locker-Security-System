/*
 ============================================================================
 Name        : Final_Project.c
 Author      : Abdelrahman Shabrawy
 Description : CONTROL_ECU
 Date        : 20/08/2023
 ============================================================================
 */

#ifndef APPLICATION_CONTROL_ECU_H_
#define APPLICATION_CONTROL_ECU_H_

#include <avr/io.h> /* To use the SREG register */
#include<util/delay.h>
/* INCLUDE HARDWARE ABSTRCTION LAYERS WHICH ARE LCD ,ULTRASONIC SENSOR */
#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/DC-MOTOR/dc_motor.h"
#include "../HAL/EEPROM/external_eeprom.h"
/* INCLUDE MICROCONTROLLER ABSTRCTION LAYERS WHICH ARE TIMER, GPIO AND UART */
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/GPIO/gpio.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/I2C/twi.h"
#include "../LIBRARIES/std_types.h"
#include "../LIBRARIES/common_macros.h"

#define READY                                              0x01
#define DONE                                               0x02
#define I_WILL_SEND_A_PASSWORD                             0x03
#define PASSWORDS_MATCH                                    0x04
#define PASSWORDS_DONOT_MATCH                              0x05
#define COMPARE_TWO_PASSWORDS                              0x06
#define CHANGE_PASSWORD                                    0x07
#define OPEN_DOOR                                          0x08
#define IS_PASSWORD_RIGHT                                  0x09
#define WRONG_PASSWORD                                      0xA
#define PASSWORD_SIZE                                       5
#define TICKS_15SECS                                        229
#define TIMER_TICKS_15SEC_STOP                              274
#define TIMER_TICKS_1MINUTE                                 915
#define MAX_WRONG_COUNTER                                   3

void recievePassword(uint8 a_arr[]);
void storePassword(void);
uint8 checkMatching(uint8 a_arr1[],uint8 a_arr2[]);
uint8 recieveCommand(void);
void sendCommand(uint8 command);
void getSavedPassword(uint8 a_arr[]);
void g_tickCounterMotor(void);
void g_tickCounterBuzzer(void);


#endif /* APPLICATION_CONTROL_ECU_H_ */
