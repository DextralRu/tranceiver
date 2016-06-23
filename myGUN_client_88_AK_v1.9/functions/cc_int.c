void CC_init() {
	//########## CC1101 INIT ################################################################
	SPI_Init();			//Инициализация SPI на максимальной скорости
	Write_Strobe(SRES);		//Сбросим СС1101
	_delay_ms(100);			//Подождем
	Write_Strobe(SRES);		//Снова сбросим
	_delay_ms(100);			//Подождем
	Write_Settings(channel);	//Положим в СС1101 настройки и частотный канал
	_delay_ms(100);			//Подождем пока очухается от восторга
	Write_Reg(SYNC1, 0x75);
	Write_Reg(SYNC0, 0x18);
	Write_Strobe(SRX);		//Перейдем в режим приема
	//#######################################################################################
}


//################################## PCINT ########################################### 
ISR(PCINT0_vect) {
    if (!GDO0) {
	GDO0CLOSE;				//прикроем-ка прерывания суда, а то замкнемся
	Write_Strobe(SIDLE);
	CRC16=0xFFFF;
	//кто-кто-кто в буферочке живет?
	tmp=(Read_Reg(RXBYTES) & 0x7F);
	if (tmp >= PACKETSIZE) {	//там вообще больше чем пакет?
	    do {
		wdt_reset(); 				//сбрасываем спящую собаку
		tmp=Read_Reg(RXFIFO);		//прочитали первый байт, должна быть длина пакета
		if (tmp==DataSizeFromRF+CRC16SIZE) {				//а длина ли это?
//		    for (uint8_t index=0; index < DataSizeFromRF; index++) { 	//читаем пакет из буфера
//			tmpDataFromRF[index]=Read_Reg(RXFIFO);
//			CRC16=_crc16_update(CRC16,tmpDataFromRF[index]);	//сразу считаем контрольную сумму
//			}
		    CRC16=Read_Burst_Reg(RXFIFO, tmpDataFromRF, DataSizeFromRF);	//читаем пакет в режиме BURST
		    wdt_reset(); 				//сбрасываем спящую собаку
		    tmpCRC16=(Read_Reg(RXFIFO)) | (Read_Reg(RXFIFO)<<8);		//а тут мы CRC прочитали из пакета
		    tmpQ=(Read_Reg(RXFIFO)) | (Read_Reg(RXFIFO)<<8);			//а тут мы RSSI прочитали из пакета
		    if (tmpCRC16==CRC16) {								//совпала?
    			if (blinkmode==0) {LED1ON;}
    			if (blinkmode==1) {LED1RE;}
    			if (blinkmode==2) {LED1OFF;}

			_delay_us(200);
			_delay_ms(address);					//ждем своей очереди во времени
			if (EnableRF!=0) {					//мамочка разрешила отвечать на запросы?
				Send_Packet(address,DataToRF,DataSizeToRF); 		//отправка ответа
			}
			if (blinkmode==0) LED1OFF;
			if (blinkmode==2) LED1ON;

			Write_Strobe(SRES);			//Снова сбросим
			_delay_ms(1);
			Write_Settings(channel);			//Положим с СС1101 настройки
			_delay_ms(1);
			Write_Reg(SYNC1, 0x75);
			Write_Reg(SYNC0, 0x18);
			Write_Strobe(SRX);  		//Включение режима RX.

			uint8_t offset=address<<2;	//смещение нащей команды
			for (uint8_t x=offset; x<offset+4; x++) {
			    if (tmpDataFromRF[x]!=DataFromRF[x]) {
				for (uint8_t x=0; x<DataSizeFromRF; x++) DataFromRF[x]=tmpDataFromRF[x];
			    command_flag=1;
			    break;
			    }
			}
			uint8_t tmpchannel=(DataFromRF[(address<<2)+0] & 0x7);	//выделили новый канал
			if ((DataFromRF[(address<<2)+0] & 0x40) && (channel!=tmpchannel)) {		//СМЕНА КАНАЛА?
				channel=tmpchannel;
				Write_Reg(CHANNR, channel);
				eeprom_write_byte(&eprom+0x01, channel);//и в eeprom впихнули
			}

//			for (uint8_t x=0; x<DataSizeFromRF; x++) {
//			DataFromRF[x]=tmpDataFromRF[x];
			//eeprom_write_byte(&eprom+0x10+x, tmpDataFromRF[x]);
//			}
//			command_flag=1;						//сигнал отработчику команды
		    }
		}
	    } while ((Read_Reg(RXBYTES) & 0x7F)>=PACKETSIZE);	//повторим пока в буффере есть что-то большее пакета
	}
	else {
	    Write_Strobe(SFRX);
	}
	GDO0OPEN;			//откроем прерывания по GDO0
	}
	Write_Reg(SYNC1, 0x75);
	Write_Reg(SYNC0, 0x18);
	Write_Strobe(SCAL);
	Write_Strobe(SRX);

}
