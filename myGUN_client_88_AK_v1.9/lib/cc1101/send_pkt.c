#include <util/crc16.h>
#include <avr/wdt.h>
#include "include/send_pkt.h"

void Send_Packet(uint8_t maddress, uint8_t *txBuffer, uint8_t datasize)
{
uint16_t CRC16=0xFFFF;
	//������ ����� ������ ������ � ����� TX FIFO.
//	LED1ON;
	wdt_reset();
	Write_Strobe(SIDLE);					//����� ��������� ������� ��������
	Write_Strobe(SFTX);					//TX FIFO ���� � �����
	Write_Reg(PKTLEN, PCKSIZE+ADDRESSSIZE+DataSizeToRF+CRC16SIZE);	//����� ������ ��� �������� + ��� ���� �����
	Write_Reg(TXFIFO, DataSizeToRF+ADDRESSSIZE+CRC16SIZE);		//����� � ����� ��������
	Write_Reg(TXFIFO, maddress);						//����� � ����� ��������
	//### ������ ������ ������ � ����� TX FIFO.
	CRC16=Write_Burst_Reg_Flash(TXFIFO, txBuffer, DataSizeToRF);	//��� ����� ����������� �����
	Write_Reg(TXFIFO, Lo(CRC16));							//������� ���� �����
	Write_Reg(TXFIFO, Hi(CRC16));							//������� ���� �����
	Write_Reg(SYNC1, 0x18);
	Write_Reg(SYNC0, 0x75);
	Write_Strobe(STX);  									//��������� ������ TX.
	wdt_reset();
	while(!GDO0);											//���������� ��������
	while(GDO0);											//�������� ��������
	Write_Reg(PKTLEN, 0xff);
	Write_Reg(SYNC1, 0x75);
	Write_Reg(SYNC0, 0x18);
	Write_Strobe(SRX);  									//��������� ������ RX.
	wdt_reset();
//	LED1OFF;
}
//==============================================================================
//
//==============================================================================
