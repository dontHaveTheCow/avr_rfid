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

int main(){

    init_spi();
    TM_MFRC522_Init();

    uint8_t id_val[5];
    uint8_t id_static[5] = {0x42, 0xbe, 0x24, 0xd9, 0x1};

	//Leds and buttons
	DDRA |= (1 << LED_PIN);
	PORTA |= (1 << LED_PIN);
    //DDRD &=~(1 << BUTTON_PIN);
    //PORTD |= (1 << BUTTON_PIN);
    DDRD &=~(1 << EXT_INT_PIN);
    PORTD |= (1 << EXT_INT_PIN);

	while(1){

        /* EXT_INTPIN is inverted */ //TODO: SLEEP WHILE NO INTERUPT RECEIVED 
        if (INPUT_PORT & (1<<EXT_INT_PIN)){

            _delay_ms(1600);
            PORTA |= (1 << LED_PIN);
            _delay_ms(150);
            PORTA &=! (1 << LED_PIN);
        }   
        else{

            PORTA |= (1 << LED_PIN);
            if (TM_MFRC522_Check(id_val) == MI_OK){
                if(TM_MFRC522_Compare(id_val, id_static) == MI_OK){
                /*
                Here is the code that should run when the car is unlocked!!!
                */
                    PORTA &= !(1 << LED_PIN);
                    PORTA ^= (1 << LED_PIN);
                    _delay_ms(250);
                    PORTA ^= (1 << LED_PIN);
                    _delay_ms(250);
                    PORTA ^= (1 << LED_PIN);
                    _delay_ms(250);
                    PORTA ^= (1 << LED_PIN);
                    _delay_ms(250);
                    PORTA ^= (1 << LED_PIN);
                    _delay_ms(250);
                    //Serial_sendStr("tag 0x42BE24D91 found\r\n");
                }
                else{
                    //Serial_sendStr("tag id no match\r\n");
                }
            }
            else{
                //Serial_sendStr("no tag around\r\n");
            }
        }   
	}
}
// ---Program------
//$ sudo avrdude -c usbasp -p t2313 -e -P usb -U flash:w:tinyButton.hex
// ---Check--------
//$ sudo avrdude -c usbasp -p t2313
// ---Erase--------
//$ sudo avrdude -c usbasp -p t2313 -e
