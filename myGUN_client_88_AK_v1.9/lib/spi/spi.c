#include "spi.h"
#include <avr/io.h>


void SPI_Init () {
	SPI_DDR |= (1<<SPI_MOSI);	//MOSI
	SPI_DDR |= (1<<SPI_SCK);	//SCK
	SPI_DDR |= (1<<SPI_SS);		//SS
	SPI_DDR &= ~(1<<SPI_MISO);	//MISO
	
	SPCR |= (1<<SPE)|(1<<MSTR);
	SPCR &= ~(1<<SPR0);
	SPCR &= ~(1<<SPR1);
        SPSR &= ~(1<<SPI2X);              // Double Clock Rate
}

