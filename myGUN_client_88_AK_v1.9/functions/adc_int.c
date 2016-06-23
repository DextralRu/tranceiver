void ADC_Init1() {
	//########## ADC voltmeter 1.1V #######################################################
	ADCSRA = 0x00;
	ADMUX	= 0xC7;  //Опорное напряжение 1.1V, канал 7.
	ADCSRA = 0x8E;   //Одиночное преобразование.
	ADCmode=0;
	ADCSRA |= (1<<ADSC);	//старт АЦП
	//#######################################################################################
}
void ADC_Init2() {
	ADCSRA =0x00;
	ADMUX	= 0x46;  //Опорное напряжение 1.1V, канал 6.
	ADCSRA = 0x8E;   //Одиночное преобразование.
	ADCSRA |= (1<<ADSC);	//старт АЦП
}



ISR(ADC_vect) {
	switch (ADCmode) {
		case 0: {
			Vpower=ADCW;
			if ((( Vpower <  170)) && (PowerCode>0x00)) {                           //напряжение 3.0В (0.52В на делителе) - ПОЛНЫЙ РАЗРЯД
				PowerCode=0x00; //EEcount=5000;					//напряжение 3.1В (0.54В) код 170 = 0% 
						//eeprom_write_byte(&eprom+xx1, Lo(Vpower));xx1++;
				}
			else
			if ((( Vpower >= 170) && (Vpower < 180)) && (PowerCode>0x10)) {
				PowerCode=0x10; //EEcount=5000;					//напряжение 3.3В (0.57В) код 212 >=20%
						//eeprom_write_byte(&eprom+xx1, Lo(Vpower));xx1++;
				}
			else
			if ((( Vpower >= 180) && (Vpower < 193)) && (PowerCode>0x20)) {
				PowerCode=0x20; //EEcount=5000;					//напряжение 3.5В (0.61В) код 237 >=40%
						//eeprom_write_byte(&eprom+xx1, Lo(Vpower));xx1++;
				}
			else
			if ((( Vpower >= 193) && (Vpower < 209)) && (PowerCode>0x30)) {
				PowerCode=0x30; //EEcount=5000;					//напряжение 3.8В (0.66В) код 266 >=60%
						//eeprom_write_byte(&eprom+xx1, Lo(Vpower));xx1++;
				}
			else
			if ((( Vpower >=  209) && (Vpower < 222)) && (PowerCode>0x40)) {
				PowerCode=0x40; //EEcount=5000;					//напряжение 4.0В (0.70В) код 28B >=80%
						//eeprom_write_byte(&eprom+xx1, Lo(Vpower));xx1++;
				}
			else
			if (( Vpower >=  222) && (PowerCode>0x50)) {
				PowerCode=0x50; //EEcount=5000;					//напряжение > 4.0В (0.70В) код 28B =100%
						//eeprom_write_byte(&eprom+xx1, Lo(Vpower));xx1++;
				}


			DataToRF[3] = (DataToRF[3] & 0x8F) | PowerCode;			//заносим код заряда в пакет
			ADC_Init2();
			ADCmode=2;
			//eeprom_write_byte(&eprom+0x20, Lo(Vpower));
			//eeprom_write_byte(&eprom+0x21, Hi(Vpower));
			break;
			}
		case 1: {
			Vgnd=ADCW;
			ADC_Init2();
			ADCmode=2;
			break;
			}
		case 2: {       
				Vspusk=ADCW;
				if ((FireStatus==5) && (Vspusk>=StartSpusk) /*&& (AmmoInTrunk==1)*/) {
					//eeprom_write_byte(&eprom+0x1F0, Lo(Vspusk));
					//eeprom_write_byte(&eprom+0x1F1, Hi(Vspusk));
					FireStatus=0;
					timerEnable=0;
				}
				if ((FireStatus==0) && (AmmoInTrunk!=0)) {
					if ((Vspusk <= FireSpusk) && (GameOn!=0))  {		//Вроде как НЕнемножко нажали - и грянул гром!
						if (GameOn)
							//lastFireStatus=1;
							FireStatus=1;					//начинаем процедуру выстрела (инфо для 1мс таймера)
							else FireStatus=0;				//запрещаем процедуру выстрела
						if (timerEnable==0) {
							timer=0;
							timerEnable=1;
						}
					}
					else {
						if ((Vspusk <= StartSpusk) && (timerEnable==0)) {//Вроде как немножко нажали
							timer=0;				//Сбросим таймер нажатия спуска
							timerEnable=1;				//и разрешим его считать
						}
						else {timerEnable=0;}
					}			       	
				}
				ADC_Init1();
				ADCmode=0;
               			break;
			}
		case 3: {
			Vgnd=ADCW;
			ADC_Init1();
			ADCmode=0;
			break;
			}
	}
}
