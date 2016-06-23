#include "include/wr_reg.h"

void Write_Reg(uint8_t addr, uint8_t value)
{
	SETCS;
	SPDR=addr;
	while(!(SPSR & (1<<SPIF)));
	SPDR=value;
	while(!(SPSR & (1<<SPIF)));
    	UNSETCS;
}
//==============================================================================
//
//==============================================================================
