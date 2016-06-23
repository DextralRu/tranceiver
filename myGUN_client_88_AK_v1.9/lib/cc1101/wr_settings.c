#include "include/wr_settings.h"
#include "include/reg_rf.h"

uint8_t Setting[44]={
 //100 кбит/с
 0x2E,  //0x00, IOCFG2   ********
 0x2E,  //0x01, IOCFG1   ********
 0x06,  //0x02, IOCFG0   ******** 
 0x45,  //0x03, FIFOTHR  ********
 0x75,  //0x04, SYNC1    ********
 0x18,  //0x05, SYNC0    ********
 0xFF,  //0x06, PKTLEN   ********
 0x04,  //0x07, PKTCTRL1 ********
 0x45,  //0x08, PKTCTRL0 ********
 0x00,  //0x09, ADDR     ********
 0x00,  //0x0A, CHANNR   ********
 0x0C,  //0x0B, FSCTRL1
 0x00,  //0x0C, FSCTRL0
 0x10,  //0x0D, FREQ2    ********
 0xA9,  //0x0E, FREQ1    ********
 0x5A,  //0x0F, FREQ0    ********
 0x5D,  //0x10, MDMCFG4
 0x3B,  //0x11, MDMCFG3
 0x13,  //0x12, MDMCFG2
 0x42,  //0x13, MDMCFG1
 0xF8,  //0x14, MDMCFG0  ********
 0x62,  //0x15, DEVIATN
 0x07,  //0x16, MCSM2    ******** 
 0x3F,  //0x17, MCSM1    ********  3f
 0x18,  //0x18, MCSM0 
 0x1D,  //0x19, FOCCFG
 0x1C,  //0x1A, BSCFG.    ********
 0xC7,  //0x1B, AGCCTRL2  ********
 0x00,  //0x1C, AGCCTRL1  ******** 
 0xB0,  //0x1D, AGCCTRL0  ******** 
 0x87,  //0x1E, WOREVT1   ********
 0x6B,  //0x1F, WOREVT0   ********
 0xF8,  //0x20, WORCTRL   ********
 0xB6,  //0x21, FREND1
 0x10,  //0x22, FREND0    ********
 0xEA,  //0x23, FSCAL3
 0x2A,  //0x24, FSCAL2
 0x00,  //0x25, FSCAL1
 0x1F,  //0x26, FSCAL0			 
 0x41,  //0x27, RCCTRL1  ********
 0x00,  //0x28, RCCTRL0  ********
 0x59,  //0x29, FSTEST   ********
 0x7F,  //0x2A, PTEST    ********
 0x3F  //0x2B, AGCTEST  ********
};


void Write_Settings(uint8_t Channel)
{
	Write_Burst_Reg_Flash(0x00, Setting, 44);
 	Write_Reg(CHANNR, Channel);
 	Write_PA_Table(0xC0);  //10 dBm output power. 1A (3A - возбуждение )
 //Write_PA_Table(0x60);  //0 dBm output power.
 //Write_PA_Table(0x40);  //-1 dBm output power.
 //Write_PA_Table(0x63);  //-2 dBm output power.
 //Write_PA_Table(0x8F);  //-3 dBm output power.
 //Write_PA_Table(0x39);  //-4 dBm output power.
 //Write_PA_Table(0x68);  //-5 dBm output power.
 //Write_PA_Table(0x6A);  //-6 dBm output power.
 //Write_PA_Table(0x36);  //-7 dBm output power.
 //Write_PA_Table(0x6D);  //-8 dBm output power.
 //Write_PA_Table(0x27);  //-9 dBm output power.
 //Write_PA_Table(0x26);  //-10 dBm output power.
 //Write_PA_Table(0x1D);  //-15 dBm output power.
 //Write_PA_Table(0x0E);  //-20 dBm output power.
 //Write_PA_Table(0x12);  //-30 dBm output power.
}


void Write_PA_Table(uint8_t value)
{
 uint8_t i;
 SETCS;
 SPDR = ( PATABLE | WRITE_BURST);   //Передача адреса с флагом BURST
 while(!(SPSR & (1<<SPIF)));     //Ожидание опустошения
 for(i = 0; i < 8; i++)
   {
    SPDR = value;          //Передача очередного байта
    while(!(SPSR & (1<<SPIF)));  //Ожидание опустошения
   }
 UNSETCS;
}
