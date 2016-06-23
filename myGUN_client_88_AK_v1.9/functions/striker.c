/**
    @file    striker.c
    @author  Белоглазов В.А. ОАО "НПО РусБИТех", ЦСИ
    @date    01.03.2015
    @brief   Файл функции "ударника"
    Данный обработчик формирует процедуру выбрасывания и загрузки патрона в патронник при ручном "передергивании" затворной рамы.
**/
ISR(STRIKERAKFUNC) {					//отрабатываем изменение состояния ударника

//if (GETSTRIKERAK) {
//	eeprom_write_byte(&eprom+0x1F0, Lo(Vspusk));
//	eeprom_write_byte(&eprom+0x1F1, Hi(Vspusk));
//  
//} else
//	{
//	eeprom_write_byte(&eprom+0x1F2, Lo(Vspusk));
//	eeprom_write_byte(&eprom+0x1F3, Hi(Vspusk));
//	}
if (GameOn) {
	sei();                                                  //вдруг надо CC1101 обработать?
		if ((FireStatus==0) && (timerEnable==0)) {	//Входим по окончании процедуры выстрела и если таймер остановлен (отпущен спусковой крючек)
			if ((GETFUSEAK==0)) {                           //Не на предохранителе?
	    			if (GETSTRIKERAK==StrikerStartPosition) { 	//Ударник взвелся?
						if (GETCARTRAGEAK==0) {         //А магазин то установлен?
	    						if (CartrageArray[1] > 0) {	//Есть что взять из магазина?
								CartrageArray[1]--;	//Забираем один из магазина
								DataToRF[2]=(DataToRF[2] & 0xE0) | CartrageArray[1];	//кол-во патронов в пакет
								AmmoInTrunk=1;				//И пихаем его в патронник
								//DataToRF[1] |= (1<<7);			//Не забываем его отметить в пакете
								DataToRF[0] |= (1<<6);			//Не забываем его отметить в пакете
							}
						//}
							else {
								AmmoInTrunk=0;			//магазин не установлен, значит из патронника выбрасываем
								DataToRF[0] |= (1<<6);
							}
						}
						else {
							AmmoInTrunk=0;			//магазин не установлен, значит из патронника выбрасываем
							DataToRF[0] |= (1<<6);
						}


				}
			}
		}
	}
}
