#include "include/rd_burst_reg.h"


uint16_t Read_Burst_Reg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
	uint16_t tmpCRC=0xFFFF;
	SETCS;
	SPDR=(addr | READ_BURST);
	while(!(SPSR & (1<<SPIF)));
	for (uint8_t index=0; index<count; index++) {
	    SPDR=0;
	    while(!(SPSR & (1<<SPIF)));
	    buffer[index]=SPDR;
	    tmpCRC=_crc16_update(tmpCRC,buffer[index]);
	}
    UNSETCS;
return(tmpCRC);
}
