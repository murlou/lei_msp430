//! Includes from GPS
#include <gps/gps.h>

//! Includes from SD-CARD
#include <mmc/pff.h>
#include <mmc/diskio.h>
#include <spi/spi.h>

//! Includes the string library (strlen)
#include <string.h>

#include <msp430.h>

//TODO Retirar depois de implementada a UART
int putchar()
{return 0;}

int
main (int argc, char *argv[])
{
FATFS fs; /* File system object */
WORD bw;
char* read;

	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
	gps_initialize();			// Initialize the GPS
	spi_initialize();			// Initialize the SPI Module
	disk_initialize();			// Initialize the card
		pf_mount(&fs);			// Mount the card
		pf_open("leitura.txt");	// Open the file on the sd-card
		
	while(1)
	{
		read=(char*)gps_read();
		pf_write(read, strlen(read), &bw);
	}

	//! The sd-card don't have support for close or umount the device
	
	return 0;
}
