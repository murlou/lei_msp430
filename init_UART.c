/**
  Biblioteca UCA0I2C

  */

#ifdef __MSP430_HAS_USCI__

int init_UART()
{  
  P3SEL|= 0x30;
  
  UCA0CTL1 |= UCSSEL1 | UCSWRST;        // Select SMCLK as clock source for UART
				        // Disable USCI module for initializations
  
  UCA0BR0 = 104;                        // 9600 Baud with 1MHz clock (Refer- 
  UCA0BR1 = 0;                          // 9600 Baud with 1MHz clock -Pg.15-22)
  UCA0CTL0 |= UC7BIT;                   // define tamanho de 8 bits para a com.
  UCA0MCTL = UCBRS0;                    // Modulation stage UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                 // Enable USCI mocule after initialization
  IE2 |= UCA0RXIE + UCA0TXIE;                      // Enable USCI_A0 RX interrupt
  
  return 0;
}

#else 

int init_UART()
{
  return -1;
}

#endif