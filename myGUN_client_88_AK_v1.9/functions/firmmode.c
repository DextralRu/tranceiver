void FirmModeTest() {
	if (firststart!=0xA5) {
		POWER5VON;
		StrikerStartPosition=GETSTRIKERAK;		//Запомним начальную позицию взведенного ударника
		LED1ON;
		_delay_ms(500);
		LED1OFF;
		FireStatus=0;
		timerEnable=0;
		while(GETFUSEAK!=0) {
			LED1ON;
			_delay_ms(10);
			LED1OFF;
			_delay_ms(100);
			LED1ON;
			_delay_ms(100);
			LED1OFF;
		}
		KLAPANAKOFF;
		LASERAKON;
	 	_delay_ms(500);
		uint16_t TmpVspuskStart=Vspusk;
		KLAPANAKON;
		_delay_ms(500);
		KLAPANAKOFF;
		LASERAKOFF;
		while(GETSTRIKERAK==StrikerStartPosition) {LED1ON;_delay_ms(10);LED1OFF;_delay_ms(10);LED1ON;_delay_ms(10);LED1OFF;}
//		while(GETSTRIKERAK!=StrikerStartPosition);
		_delay_ms(1000);
		uint16_t TmpVspuskFire=Vspusk;
		LED1ON;
		uint8_t TmpVspuskDelta=(TmpVspuskStart-TmpVspuskFire)/10;
		TmpVspuskStart=TmpVspuskStart-TmpVspuskDelta;
		eeprom_write_byte(&eprom+0x10, Lo(TmpVspuskStart));			//Сохраним значение VspuskStart
                eeprom_write_byte(&eprom+0x11, Hi(TmpVspuskStart));
		eeprom_write_byte(&eprom+0x12, Lo(TmpVspuskFire));              	//Сохраним значение VspuskFile
		eeprom_write_byte(&eprom+0x13, Hi(TmpVspuskFire));
		eeprom_write_byte(&eprom+0x14, StrikerStartPosition);		//Сохраним значение взведенного ударника
		eeprom_write_byte(&eprom+0x03, 0xA5);
		while(1) {
			LED1ON;
			_delay_ms(100);
			LED1OFF;
			_delay_ms(300);
			LED1ON;
			_delay_ms(100);
			LED1OFF;
			_delay_ms(1000);
		}
	}
	else
		{
		 StartSpusk=((eeprom_read_byte(&eprom+0x10)) | (eeprom_read_byte(&eprom+0x11))<<8);
		 FireSpusk=((eeprom_read_byte(&eprom+0x12)) | (eeprom_read_byte(&eprom+0x13))<<8);
		 StrikerStartPosition=eeprom_read_byte(&eprom+0x14);
		}


	LASERAKOFF;
	KLAPANAKOFF;
	POWER5VON;
	_delay_ms(100);
	for (uint8_t x=0; x<200; x++) {
		if ((GETCARTRAGEAK) &&
		    (GETSINGLEAK) &&
		    (Vspusk <= FireSpusk)) {blinkmode=1;_delay_ms(5);}
			else {blinkmode=0;break;}
	}
	if (blinkmode==1) {
		PowerOn=0x20;	//сразу включимся
		LaserOn=0x10;	//сразу включимся
		GameOn=0x08;	//мы в игре
		powermode=1;
		for (uint8_t x=0; x<200; x++) {
			if ((GETCARTRAGEAK) &&
		    	(!GETSINGLEAK) &&
		    	(Vspusk <= FireSpusk)) {blinkmode=3;_delay_ms(5);}
				else {blinkmode=1;break;}
		}
	}
	else {
		for (uint8_t x=0; x<200; x++) {
			if ((GETCARTRAGEAK) &&
	    		(!GETSINGLEAK) &&
	    		(Vspusk <= FireSpusk)) {blinkmode=3;_delay_ms(5);}
				else {blinkmode=0;break;}
		}
	}
	if (blinkmode==0) POWER5VOFF;
	if (blinkmode==3) {
		address++;
		if (address>0x07) address=0;
		eeprom_write_byte(&eprom+0x00, address);	//Запишем новое значение адреса
		LED1ON;
		_delay_ms(1000);
		LED1OFF;
		_delay_ms(500);
		LED1ON;
		_delay_ms(500);
		LED1OFF;
	}
}


