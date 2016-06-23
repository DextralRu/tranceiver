#include <util/crc16.h>
#include <avr/wdt.h>
#include "include/send_pkt.h"

void Send_Packet(uint8_t maddress, uint8_t *txBuffer, uint8_t datasize)
{
uint16_t CRC16=0xFFFF;
	//запись длины пакета данных в буфер TX FIFO.
//	LED1ON;
	wdt_reset();
	Write_Strobe(SIDLE);					//пусть генератор немного отдохнет
	Write_Strobe(SFTX);					//TX FIFO всех с пляжа
	Write_Reg(PKTLEN, PCKSIZE+ADDRESSSIZE+DataSizeToRF+CRC16SIZE);	//длина пакета при передаче + сам байт длины
	Write_Reg(TXFIFO, DataSizeToRF+ADDRESSSIZE+CRC16SIZE);		//длину в пакет поместим
	Write_Reg(TXFIFO, maddress);						//адрес в пакет поместим
	//### запись пакета данных в буфер TX FIFO.
	CRC16=Write_Burst_Reg_Flash(TXFIFO, txBuffer, DataSizeToRF);	//без длины контрольной суммы
	Write_Reg(TXFIFO, Lo(CRC16));							//младший байт суммы
	Write_Reg(TXFIFO, Hi(CRC16));							//старший байт суммы
	Write_Reg(SYNC1, 0x18);
	Write_Reg(SYNC0, 0x75);
	Write_Strobe(STX);  									//¬ключение режима TX.
	wdt_reset();
	while(!GDO0);											//происходит передача
	while(GDO0);											//передача окончена
	Write_Reg(PKTLEN, 0xff);
	Write_Reg(SYNC1, 0x75);
	Write_Reg(SYNC0, 0x18);
	Write_Strobe(SRX);  									//¬ключение режима RX.
	wdt_reset();
//	LED1OFF;
}
//==============================================================================
//
//==============================================================================
