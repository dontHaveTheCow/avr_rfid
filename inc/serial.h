#ifndef SERIAL_LIBRARY
#define SERIAL_LIBRARY

#include <avr/io.h>

#define BAUD_9600 9600
#define BAUD_4800 4800

//These are the prototypes for the routines
void Serial_init();
void Serial_send(uint8_t data);
void Serial_sendStr(char* string);
//uint16_t Serial_rec(void);

#endif