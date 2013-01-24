#include <gps.h>

int gps_initialize(void)
{
	uart_initialize();
#ifdef __MSP430G2553
	uart_set_bitrate(4800);
#endif
	
	return 1;
}


const char *gps_read(void)
{
char read[40];
char c;
int i=0;	
	
	do
	{
		c=getchar();
		read[i++]=c;
	}while((c!='$') || (i<40-1));
	read[i]='\0';
	
	if(i>=40)
		return (char*)EOF; /*Out of memory*/
	
	return "OK!";
}
