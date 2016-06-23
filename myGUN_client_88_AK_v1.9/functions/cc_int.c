void CC_init() {
	//########## CC1101 INIT ################################################################
	SPI_Init();			//������������� SPI �� ������������ ��������
	Write_Strobe(SRES);		//������� ��1101
	_delay_ms(100);			//��������
	Write_Strobe(SRES);		//����� �������
	_delay_ms(100);			//��������
	Write_Settings(channel);	//������� � ��1101 ��������� � ��������� �����
	_delay_ms(100);			//�������� ���� ��������� �� ��������
	Write_Reg(SYNC1, 0x75);
	Write_Reg(SYNC0, 0x18);
	Write_Strobe(SRX);		//�������� � ����� ������
	//#######################################################################################
}


//################################## PCINT ########################################### 
ISR(PCINT0_vect) {
    if (!GDO0) {
	GDO0CLOSE;				//��������-�� ���������� ����, � �� ���������
	Write_Strobe(SIDLE);
	CRC16=0xFFFF;
	//���-���-��� � ��������� �����?
	tmp=(Read_Reg(RXBYTES) & 0x7F);
	if (tmp >= PACKETSIZE) {	//��� ������ ������ ��� �����?
	    do {
		wdt_reset(); 				//���������� ������ ������
		tmp=Read_Reg(RXFIFO);		//��������� ������ ����, ������ ���� ����� ������
		if (tmp==DataSizeFromRF+CRC16SIZE) {				//� ����� �� ���?
//		    for (uint8_t index=0; index < DataSizeFromRF; index++) { 	//������ ����� �� ������
//			tmpDataFromRF[index]=Read_Reg(RXFIFO);
//			CRC16=_crc16_update(CRC16,tmpDataFromRF[index]);	//����� ������� ����������� �����
//			}
		    CRC16=Read_Burst_Reg(RXFIFO, tmpDataFromRF, DataSizeFromRF);	//������ ����� � ������ BURST
		    wdt_reset(); 				//���������� ������ ������
		    tmpCRC16=(Read_Reg(RXFIFO)) | (Read_Reg(RXFIFO)<<8);		//� ��� �� CRC ��������� �� ������
		    tmpQ=(Read_Reg(RXFIFO)) | (Read_Reg(RXFIFO)<<8);			//� ��� �� RSSI ��������� �� ������
		    if (tmpCRC16==CRC16) {								//�������?
    			if (blinkmode==0) {LED1ON;}
    			if (blinkmode==1) {LED1RE;}
    			if (blinkmode==2) {LED1OFF;}

			_delay_us(200);
			_delay_ms(address);					//���� ����� ������� �� �������
			if (EnableRF!=0) {					//������� ��������� �������� �� �������?
				Send_Packet(address,DataToRF,DataSizeToRF); 		//�������� ������
			}
			if (blinkmode==0) LED1OFF;
			if (blinkmode==2) LED1ON;

			Write_Strobe(SRES);			//����� �������
			_delay_ms(1);
			Write_Settings(channel);			//������� � ��1101 ���������
			_delay_ms(1);
			Write_Reg(SYNC1, 0x75);
			Write_Reg(SYNC0, 0x18);
			Write_Strobe(SRX);  		//��������� ������ RX.

			uint8_t offset=address<<2;	//�������� ����� �������
			for (uint8_t x=offset; x<offset+4; x++) {
			    if (tmpDataFromRF[x]!=DataFromRF[x]) {
				for (uint8_t x=0; x<DataSizeFromRF; x++) DataFromRF[x]=tmpDataFromRF[x];
			    command_flag=1;
			    break;
			    }
			}
			uint8_t tmpchannel=(DataFromRF[(address<<2)+0] & 0x7);	//�������� ����� �����
			if ((DataFromRF[(address<<2)+0] & 0x40) && (channel!=tmpchannel)) {		//����� ������?
				channel=tmpchannel;
				Write_Reg(CHANNR, channel);
				eeprom_write_byte(&eprom+0x01, channel);//� � eeprom ��������
			}

//			for (uint8_t x=0; x<DataSizeFromRF; x++) {
//			DataFromRF[x]=tmpDataFromRF[x];
			//eeprom_write_byte(&eprom+0x10+x, tmpDataFromRF[x]);
//			}
//			command_flag=1;						//������ ����������� �������
		    }
		}
	    } while ((Read_Reg(RXBYTES) & 0x7F)>=PACKETSIZE);	//�������� ���� � ������� ���� ���-�� ������� ������
	}
	else {
	    Write_Strobe(SFRX);
	}
	GDO0OPEN;			//������� ���������� �� GDO0
	}
	Write_Reg(SYNC1, 0x75);
	Write_Reg(SYNC0, 0x18);
	Write_Strobe(SCAL);
	Write_Strobe(SRX);

}
