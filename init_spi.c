/**
  Biblioteca da ativação do UCA0SPI


*/

#ifdef __MSP430_HAS_USCI__


/*
* Funcao para realizar a incializacao do spi.
*
* \param a Inteiro que conta o numero de placas do fujioka.
* \return 0 
  \see {}
*/
int init_spi()
{
  P3SEL |= 0x11;                            // P3.0,4 USCI_A0 option select
  UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 |= 0x02;
  UCA0BR1 = 0;
  UCA0MCTL = 0;
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

return 0;
} 

#else

int init_spi()
{
  return -1;
}
#endif