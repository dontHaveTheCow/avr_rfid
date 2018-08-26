#include "spi.h"

void init_spi(){

    //Clock is low when idle
    //Data sampled at 1st edge
    //First bit MSB;

    //inputs
    DDRB &=~ (1 << SPI_SDI);
    //outputs
    DDRB |= (1<<SPI_SCK)|(1<<SPI_SDO)|(1<<SPI_CS);
    //USIWM0 -              Three wire mode
    //USICS1 and USICLK -   External clock, positive edge
    USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK);

//  if (speed==1) { 
//         PORTB |= (1<<SPI_SDO)|(1<<SPI_CS);  // pull-up i.e. disabled     
//         DDRB = (1<<SPI_SCK)|(1<<SPI_SDI)|(1<<SPI_CS);
//         USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK);
//     } else { // Si speed es 0....
//         PORTB |= (1<<SPI_CS);     // pull-up i.e. disabled   
//         DDRB &= ~((1<<SPI_SCK)|(1<<SPI_SDO)|(1<<SPI_SDI)|(1<<SPI_CS));
//         USICR = 0;
//     } 
}

uint8_t TM_SPI_Send(uint8_t data){

    USIDR = data; // Carga el dato a enviar.
    USISR = (1<<USIOIF);
    do {
        USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC); // Configuramos la USI.
    } while ((USISR & (1<<USIOIF)) == 0); // En caso de que termine de enviar el dato, retorna el valor
	                                        // De USIDR. 
    return USIDR; 	

}