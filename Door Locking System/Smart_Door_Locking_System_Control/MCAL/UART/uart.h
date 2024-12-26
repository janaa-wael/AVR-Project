/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../LIB/std_types.h"

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
void UART_init(uint32 baud_rate);

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

typedef enum {
	TX_DISABLED,
	TX_ENABLED
}UART_TransmitterEnable;

typedef enum {
	RX_DISABLED,
	RX_ENABLED
}UART_ReceiverEnable;

typedef enum {
	DISABLED_U2X,
	ENABLED_U2X
}UART_DoubleSpeedMode;

typedef enum {
	ASYNCHRONOUS_MODE,
	SYNCHRONOUS_MODE
}UART_OperationMode;

typedef enum {
	FIVE_BITS,
	SIX_BITS,
	SEVEN_BITS,
	EIGHT_BITS,
	NINE_BITS=8
}UART_CharacterSize;

typedef enum {
	PARITY_DISABLED,
	EVEN_PARITY=2,
	ODD_PARITY=3
}UART_ParityMode;

typedef enum {
	ONE_STOP_BIT,
	TWO_STOP_BIT
}UART_StopBit;

typedef enum {
	ASYNCHRONOUS_MODE_CLK,
	SYNCHRONOUS_MODE_CLK
}UART_ClockPolarity;

typedef enum {
	BR_2400,BR_4800,BR_9600,BR_19200,BR_28800,BR_38400
}UART_BaudRateType;

typedef struct {
	UART_CharacterSize bit_data;
	UART_ParityMode parity;
	UART_StopBit stop_bit;
	UART_BaudRateType baud_rate;
}UART_ConfigType;


#endif /* UART_H_ */
