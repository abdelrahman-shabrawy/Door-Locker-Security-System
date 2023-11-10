/*
 ============================================================================
 Name        : Final_Project.c
 Author      : Abdelrahman Shabrawy
 Description : HMI_ECU
 Date        : 20/08/2023
 ============================================================================
 */

#ifndef APPLICATION_HML_ECU_H_
#define APPLICATION_HML_ECU_H_
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h>

/* INCLUDE HARDWARE ABSTRCTION LAYERS WHICH ARE LCD ,ULTRASONIC SENSOR */
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/LCD/lcd.h"
/* INCLUDE MICROCONTROLLER ABSTRCTION LAYERS WHICH ARE TIMER, GPIO AND UART */
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/GPIO/gpio.h"
#include "../MCAL/UART/uart.h"
#include "../LIBRARIES/std_types.h"


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

void createandStorePassword(void);
void SendPassword(uint8 a_arr[]);
void sendCommand(uint8 command);
uint8 recieveCommand(void);
void mainFucntion(void);
void wrongPasswordScreen(void);
void enterPassword(uint8 x[]);
void PasswordDONTMATCHScreen(void);
void ALERTscreen(void);
void lockingUnlockingScreen(void);
void g_tickCounterMotor(void);
void g_tickCounterAlarm(void);



#endif /* APPLICATION_HML_ECU_H_ */
