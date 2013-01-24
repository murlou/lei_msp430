#include <uart.h>

#ifndef __MSP430_HAS_USCI__
#error "Error! This MCU doesn't have a USCI peripheral"
#endif /*__MSP430_HAS_USCI__*/

int uart_initialize()
{

#ifdef __MSP430G2553
	P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
#endif /*__MSP430G2553*/

	UCA0CTL1 |= UCSSEL1 | UCSWRST;        // Select SMCLK as clock source for UART
					    // Disable USCI module for initializations

	UCA0BR0 = 104;                        // 9600 Baud with 1MHz clock (Refer- 
	UCA0BR1 = 0;                          // 9600 Baud with 1MHz clock -Pg.15-22)
	UCA0CTL0 |= UC7BIT;                   // define tamanho de 8 bits para a com.
	UCA0MCTL = UCBRS0;                    // Modulation stage UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                 // Enable USCI mocule after initialization
	IE2 |= UCA0RXIE + UCA0TXIE;                      // Enable USCI_A0 RX interrupt

	return SUCCESS;


}

int uart_set_bitrate(unsigned int rate)
{
	BCSCTL1 = CALBC1_16MHZ;                    // Set DCO
	DCOCTL = CALDCO_16MHZ;

	UCA0BR0 = (long int)(16000000/rate); //104;                         // 16MHz 9600
	UCA0BR1 = ((long int)(16000000/rate) ) >> 8;                        // 16MHz 9600

	return (UCA0BR0 - (16000000*rate) ) + (UCA0BR1- ((16000000*rate) << 8) );
}

int uart_close()
{
	IE2 &= ~(UCA0RXIE + UCA0TXIE);                      // Desable USCI_A0 RX interrupt
	
	return IE2 && (UCA0RXIE + UCA0TXIE);
}

int getchar()
{
	while (!(IFG2&UCA0RXIFG));			// Wait recive a data

	return UCA0RXBUF=='\r'?'\n' : UCA0RXBUF;
}

int putchar(volatile int c)
{
	if(UCA0CTL1 & UCSWRST) return EOF; // USCI not active

	while (!(IFG1 & UCA0TXIFG)); // wait for USART TX buffer ready
	UCA0TXBUF = c;

	IE2 |= UCA0TXIE;                       // Enable USCI_A0 TX interrupt
//__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled

	return c;
}


/**
 * Interrupr function from TX of USCI 0
 * It's just commute P1.0 ( OUTPUT LED )
 */
interrupt(USCIAB0TX_VECTOR) USCI0TX_ISR(void)
{
	__bic_SR_register_on_exit(LPM0_bits + GIE);
}
