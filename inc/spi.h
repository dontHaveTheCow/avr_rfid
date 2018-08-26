#ifndef SPI_LIBRARY
#define SPI_LIBRARY

#include <avr/io.h>

// Definimos los pines para la comunicaciÃ³n SPI.
#define SPI_SDI PINB5  // Pin B5 como MOSI.
#define SPI_SDO PINB6  // Pin B4 como MISO.
#define SPI_SCK PINB7  // Pin B7 como SPI_SCK.
#define SPI_CS  PINB4
#define SPI_PORT PORTB

#define spi_cs_low() SPI_PORT &=~ (1 << SPI_CS);
#define spi_cs_high() SPI_PORT |= (1 << SPI_CS);

void init_spi(void);
uint8_t TM_SPI_Send(uint8_t data);

#endif 
