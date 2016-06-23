#include "include/wr_strobe.h"
#include <util/delay.h>

void Write_Strobe(uint8_t strobe)
{
	SETCS;
	_delay_us(10);
	SPDR=strobe;
	while(!(SPSR & (1<<SPIF)));
    UNSETCS;
}
