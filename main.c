#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

//user libs
#include "spi.h"
#include "rfid.h"

#define LED_PIN PINA1
#define EXT_INT_PIN PIND2
#define BUTTON_PIN PIND3
#define BUTTON_NUMBER 3
#define INPUT_PORT PIND

typedef enum {
	NO_IGNITION = 0,
	IGNITION_NO_TAG,
	IGNITION_WITH_TAG
} Sikretka_State_t;

Sikretka_State_t globalState = NO_IGNITION;

int main(){

    init_spi();
    TM_MFRC522_Init();

    uint8_t id_val[5];
    uint8_t id_static[5] = {0x42, 0xbe, 0x24, 0xd9, 0x1};

	//Leds and buttons
	DDRA |= (1 << LED_PIN);
	PORTA |= (1 << LED_PIN);
    DDRD &=~(1 << EXT_INT_PIN);
    PORTD |= (1 << EXT_INT_PIN);
    //DDRD &=~(1 << BUTTON_PIN);
    //PORTD |= (1 << BUTTON_PIN);
    //_SFR_IO8(0x3B) |= ( 1 << INT1 ); //Enable interrupt INT1
	//MCUCR |= (1 << ISC11); //Falling edge on INT1
	//sei();

	while(1){

        if (globalState == NO_IGNITION){

            _delay_ms(1600);
            PORTA |= (1 << LED_PIN);
            _delay_ms(150);
            PORTA &=! (1 << LED_PIN);
            
            /* EXT_INTPIN is inverted */ 
            if ((!INPUT_PORT) & (1<<EXT_INT_PIN)){
                //Change state
                globalState = IGNITION_NO_TAG; /*!!!!!!Condition!!!!!!!!*/
            }
        }
        else if(globalState == IGNITION_NO_TAG){
            
            PORTA ^= (1 << LED_PIN);
            _delay_ms(250);
            //Check whether there is a tag around...
            if (TM_MFRC522_Check(id_val) == MI_OK){
                //Check whether the right id is found...
                if(TM_MFRC522_Compare(id_val, id_static) == MI_OK){
                    //Serial_sendStr("tag 0x42BE24D91 found\r\n");
                    //Turn off led, change state...
                    globalState = IGNITION_WITH_TAG;

                    //Shut on relay

                }
                else{
                    //Serial_sendStr("tag id no match\r\n");
                }
            }
            else{
                //Serial_sendStr("no tag around\r\n");
            }
        }
        else if(globalState == IGNITION_WITH_TAG){

            if (INPUT_PORT & (1<<EXT_INT_PIN)){

                //If ignition was turn off, return to default state
                globalState = NO_IGNITION;

                //Shut off relay
            }
        }
	}
}

//ISR (INT1_vect){
//    
//}

//ISR (USART_RX_vect) {
//
// receiveData = UDR;
// if (receiveData == 0b01010101)
	// PORTA ^= (1 << LED_PIN);
//}


// ---Program------
//$ sudo avrdude -c usbasp -p t2313 -e -P usb -U flash:w:tinyButton.hex
// ---Check--------
//$ sudo avrdude -c usbasp -p t2313
// ---Erase--------
//$ sudo avrdude -c usbasp -p t2313 -e
