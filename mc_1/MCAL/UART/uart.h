/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Abdelrahman Shabrawy
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

//UART_ConfigType UART_Configrations = {EIGHT_BIT,DISABLED,ONE_BIT,9600};

#include "../../LIBRARIES/std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	BIT_5,BIT_6,BIT_7,BIT_8,RESERVED,RESERVED_5,RESERVED_6,BIT_9
}UART_BitData;

typedef enum
{
	DISABLED,RESERVED_PARITY,EVEN_PARITY,ODD_PARITY
}UART_Parity;

typedef enum
{
	ONE_BIT,TWO_BIT
}UART_StopBit;

typedef uint32 UART_BaudRate ;

typedef struct
{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
