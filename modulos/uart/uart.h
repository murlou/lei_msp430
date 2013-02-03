#ifndef __UART_H__
#define __UART_H__
#ifndef __UART_H__
#define __UART_H__

/**
\section{Teste}
conteudo de teste randomico
*/


#include <legacymsp430.h>

#include <msp430.h>
#include <stdio.h>
#include <myerrno.h>



#ifdef __MSP430G2553

	//!TODO: Set the pins for every device
	#define RX_PIN
	#define TX_PIN
	#define clk_speed //!TODO: Set clock speed for MSP430G2553

	/**
	Set a specific bit rate different from the standard bit rate
		@param unsigned int rate : the new bit rate that will be set on uart module
		@return Return the difference from the rate wanted and the one that was set
	*/
	extern
	int uart_set_bitrate(unsigned int rate);

#endif
//MSP430f2274
#ifdef __MSP430F2274

	#define RX_PIN 0x30// P3.4 - TX
	#define TX_PIN 0x10// P3.5 - RX
	#define clk_speed 1000000 // 1Mhz
	/**
	Set a specific bit rate different from the standard bit rate
		@param unsigned int rate : the new bit rate that will be set on uart module
		@return Return the difference from the rate wanted and the one that was set
	*/
	extern
	int uart_set_bitrate(unsigned int rate);

#endif

/**
Initialize the uart module with the default bit rate
	@return Return the difference from the rate standard and the one that was set
*/
extern
int uart_initialize();

/**
Close the module of the uart
	@return Return if the module was full disabled or not
	0: Even the specific interrupt as the global interrupt was disabled
	1: The global interrupt still enabled
*/
extern
int uart_close();

/**
Default function that capture a char from the standard input
	@return Character captured
*/
extern
int getchar();

/**
Default function that print a char on the standard output
	@return Return the character written as an unsigned char cast to an int or EOF on error.
*/
extern
int putchar(int ch);

#endif
