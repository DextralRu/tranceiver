#include "include/rd_reg.h"

uint8_t Read_Reg(uint8_t addr)
{
	SETCS;
	SPDR=(addr | READ_SINGLE);
	while(!(SPSR & (1<<SPIF)));
	SPDR=0;
	while(!(SPSR & (1<<SPIF)));
    UNSETCS;
    return SPDR;
}

//==============================================================================
//
//==============================================================================
