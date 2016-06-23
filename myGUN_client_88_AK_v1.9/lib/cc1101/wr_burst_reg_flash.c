#include <stdio.h>
#include "include/wr_burst_reg_flash.h"

uint16_t Write_Burst_Reg_Flash(uint8_t addr, uint8_t *buffer, uint8_t count)
{
 register uint8_t i;
 register uint16_t CRC16=0xFFFF;
 SETCS;
 SPDR = (addr | WRITE_BURST);   //�������� ������ � ������ BURST
 while(!(SPSR & (1<<SPIF)));     //�������� �����������
 for(i = 0; i < count; i++)
   {
    SPDR = buffer[i];          //�������� ���������� �����
	CRC16=_crc16_update(CRC16,buffer[i]);	//����� ������� ����������� �����
    while(!(SPSR & (1<<SPIF)));  //�������� �����������
   }
 UNSETCS;
 return(CRC16);
}
//==============================================================================
//
//==============================================================================
