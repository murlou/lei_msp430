/**
 * File: usci_spi.c - msp430 USCI SPI implementation
 *
 */
#include <msp430.h>
#include <stdint.h>
#include "spi.h"

#ifndef __MSP430_HAS_USCI__
#error "Error! This MCU doesn't have a USCI peripheral"
#endif

/**
 * USCI flags for various the SPI MODEs
 *
 * Note: The msp430 UCCKPL tracks the CPOL value. However,
 * the UCCKPH flag is inverted when compared to the CPHA
 * value described in Motorola documentation.
 */

#define SPI_MODE_0 (UCMSB | UCMST | UCSYNC | UCCKPH)    		/* CPOL=0 CPHA=0 */
#define SPI_MODE_1 (UCMSB | UCMST | UCSYNC)         			/* CPOL=0 CPHA=1 */
#define SPI_MODE_2 (UCMSB | UCMST | UCSYNC | UCCKPL | UCCKPH)	/* CPOL=1 CPHA=0 */
#define SPI_MODE_3 (UCMSB | UCMST | UCSYNC | UCCKPL)			/* CPOL=1 CPHA=1 */

/**
 * utility macros for extracting hi/lo byte data from a word value
 */
#ifndef LOBYTE
#define LOBYTE(w) ((w)&0xFF)
#define HIBYTE(w) ((w)>>8)
#endif

/**
 * spi_initialize() - Configure USCI UCB0 for SPI mode
 *
 * P2.0 - CS (active low)
 * P1.5 - SCLK
 * P1.6 - SIMO/MOSI
 * P1.7 - SOMI/MISO
 */
int spi_initialize() {

#ifdef __MSP430G2553
	UCB0CTL1 = UCSWRST | UCSSEL_2; // Put USCI in reset mode, source USCI clock from SMCLK
    UCB0CTL0 = SPI_MODE_0; // Use SPI MODE 0 - CPOL=0 CPHA=0
    
	P1SEL |= BIT5 | BIT6 | BIT7; // configure P1.5, P1.6, P1.7 for USCI
    P1SEL2 |= BIT5 | BIT6 | BIT7;

    P2OUT |= BIT0; // CS on P2.0. start out disabled
    P2DIR |= BIT0; // CS configured as output
	
	UCB0BR0 = LOBYTE(SPI_400kHz); // set initial speed to 400kHz (16MHz/400000)
    UCB0BR1 = HIBYTE(SPI_400kHz);

    UCB0CTL1 &= ~UCSWRST; // release USCI for operation
	return success;
#endif
    
#ifdef __MSP430F2274
						//DETALHE: Nesse modo, P3.0 -- Master CLK
						//					   P3.4 -- UCASIMO
						//					   P3.5 -- UCASOMI
						
	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0CTL0 |= SPI_MODE_0; // 3-pin, 8-bit SPI master
	
	P3SEL |= BIT0 | BIT4 | BIT5 |; // P3.0, P3.4, P3.5 USCI_A0 option select
	
	UCA0BR0 |= 0x02;		// Initial speed BRCLK = SMCLK/2 = 1.2Mhz/2 = 600 mHz
	UCA0BR1 = 0;
	UCA0MCTL = 0;
	
	UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
	return success;
#endif
	
}

/**
 * spi_send() - send a byte and recv response
 */
uint8_t spi_send(const uint8_t c) {
    while (!(IFG2 & UCB0TXIFG))
        ; // wait for previous tx to complete

    UCB0TXBUF = c; // setting TXBUF clears the TXIFG flag

    while (!(IFG2 & UCB0RXIFG))
        ; // wait for an rx character?

    return UCB0RXBUF; // reading clears RXIFG flag
}

/**
 * spi_receive() - send dummy btye then recv response
 */

uint8_t spi_receive(void) {

    while (!(IFG2 & UCB0TXIFG))
        ; // wait for any previous xmits to complete

    UCB0TXBUF = 0xFF; // Send dummy packet to get data back.

    while (!(IFG2 & UCB0RXIFG))
        ; // wait to recv a character?

    return UCB0RXBUF; // reading clears RXIFG flag
}

/**
 * spi_set_divisor() - set new clock divider for USCI
 *
 * USCI speed is based on the SMCLK divided by BR0 and BR1
 * initially we start slow (400kHz) to conform to SDCard
 * specifications then we speed up once initialized (SPI_DEFAULT_SPEED)
 *
 * returns the previous setting
 */

uint16_t spi_set_divisor(const uint16_t clkdiv) {
    uint16_t prev_clkdiv = UCB0BR1 << 8 | UCB0BR0;

    UCB0CTL1 |= UCSWRST; // go into reset state
    UCB0BR0 = LOBYTE(clkdiv);
    UCB0BR1 = HIBYTE(clkdiv);
    UCB0CTL1 &= ~UCSWRST; // release for operation

    return prev_clkdiv;
}
