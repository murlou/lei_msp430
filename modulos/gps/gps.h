#ifndef _GPS
#define _GPS

#include <uart/uart.h>


//! Initialize the GPS and if necessery, the UART
extern
int gps_initialize(void);

//!Read a data from the GPS
extern
const char *gps_read(void);

#endif
