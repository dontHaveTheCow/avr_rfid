#include "serial.h"

void Serial_init(void){

	//UART
	//int UBBRValue = 12; //Baud 4800 - when U2X = 0
	//int UBBRValue = 6; //Baud 9600 - when U2X = 0 (big error!!! -7.0%)
	int UBBRValue = 12; //Baud 9600 - U2X = 1
	//Put the upper part of the baud number here (bits 8 to 11)
	UBRRH = (unsigned char) (UBBRValue >> 8);
	//Put the remaining part of the baud number here
	UBRRL = (unsigned char) UBBRValue;
	//Enable double speed mode
	UCSRA |= (1 << U2X);
	//Enable the receiver and transmitter
	UCSRB |= (1 << TXEN);
	//Set 2 stop bits and data bit length is 8-bit
	UCSRC |=  (1 << UCSZ0) | (1 << UCSZ1);
}

void Serial_send(uint8_t data)
{
    while ((UCSRA & (1 << UDRE)) == 0);
    UDR = data;
}

void Serial_sendStr(char* string){
	while(*string != 0){
		Serial_send(*string++);
	}
}

// uint16_t Serial_rec(void)
// {
// 	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
// 	return USART_ReceiveData(USART1);
// }
