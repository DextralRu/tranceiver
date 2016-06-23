/**
    @file    timer1ms.c
    @author  ���������� �.�. ��� "��� ��������", ���
    @date    01.03.2015
    @brief   ���� ������� ����������� 1�� ������������� �������
    ������ ���������� ����� ������ ������� ������� ���������� ������ � ��������� ��� ������ ������������ ��������� ��������.
    ����������� ���������� �������� ��������� ������������ ��������� ���������� ��������-�������� �������, � ��� �� ��������
    ���������� ������� �� �������� � ���������. ����������� ������ ������������ ���������� �������� ��������� ������� ���������
    ���������� ������ � ����������� ���.
**/

ISR(TIMER2_COMPB_vect) { 
	if (timerEnable==1) {			//������� ����� ������� ���������� �����
	    timer++;
	    uint16_t tmp=timer/10;		//� ������ ��� ���������� � ��������� 10��
	    DataToRF[8]=Hi(tmp);
	    DataToRF[9]=Lo(tmp);
	}							//��� �������, ���� �� ���������� ������� ���������� �� �������, ����� ������ ������������ ��������


	if ((!CartrageTrigger) && (AmmoInTrunk==0) && ((FireStatus==3) || (FireStatus==4))) {	//��������� ������, �������� ���������
		if ((GETCARTRAGEAK==0)) {                               //������� ����������
	    		if (CartrageArray[1] > 0) {	//� �������� ��� ���� �������?
			CartrageArray[1]--;		//�������� ���� �� ��������
			DataToRF[2]=(DataToRF[2] & 0xE0) | CartrageArray[1];	//���-�� �������� � �����
			AmmoInTrunk=1;					//� ������ ��� � ���������
			//DataToRF[1] |= (1<<7);				//��� � �����
			DataToRF[0] |= (1<<6);				//��� � �����
			}
			EventFire=0;			//���� ����� ��������
			DataToRF[1] &=~(1<<7);		//��� � �����
		    	if (!GETSINGLEAK) {FireStatus=5;}		//��������� �������� ��� ���������� ���������
				else {
					if (AmmoInTrunk==0) FireStatus=5;	//��� ��� ��������� ������ ��� ��������� ��������
						else FireStatus=0;              //��� ��� ��������� ������ ��� �������� ��������
				}			//��������� ��� ������� ���������
		}
	}


	if ((FireStatus==2)) {      			//������ ������ ������������ ��������
	    if (FireTimer>0) {                          //��� �� ��������� ����� ��������� �������?
	    	if (EventFire==0) {
			FiredAmmoCount++; 
			DataToRF[6]=FiredAmmoCount;
			} //������ ������ ������ ��������. ����������� ���-�� ���������.
		EventFire=1;				//���� ������ �������� (�� � ���, ��� ������ ���)
		DataToRF[1] |=(1<<7);			//��� � �����
		KLAPANAKON;                             //��������� ������ (�� � ���, ��� ������ ���)
		DataToRF[0]|=(1<<4);			//������� ������ - � �����
		FireTimer--;				//��������� �����
		}
		else {                                  //���� ������� �� ���������� ������ ���
		    if (FireDelay>0) {                  //����� �� ���������� ��� ����?
			AmmoInTrunk=0;			//� ���������� ������ ����� ����� (�� � ���, ��� ������ ���)
			KLAPANAKOFF;			//��������� ������ (�� � ���, ��� ������ ���)
			DataToRF[0]&=~(1<<4);		//������� ������� - � �����
			FireDelay--;			//��������� ����� ���������� �������
//			EventFire=0;			//���� ����� ��������
//			DataToRF[1] &=~(1<<7);		//��� � �����
			}
			else {
			    if (!GETSINGLEAK) {FireStatus=3;}		//��������� �������� ��� ���������� ���������
				else {FireStatus=4;}			//��������� ��� ������� ���������
			    }
		    }
		}
		else {
			FireStatus=0; FireTimer=0; FireDelay=0;
		}



	if ((FireStatus==1) && (AmmoInTrunk==1)) {FireStatus=2; FireTimer=KlapanOnTime; FireDelay=PauseTime;} //���������� ������ ��� ��������� ��������
	if ((FireStatus==1) && (AmmoInTrunk==0)) {FireStatus=0; FireTimer=0; FireDelay=0;}











/*
	EEcount++;
	if (EEcount>=5000) {
		eeprom_write_byte(&eprom+0x100, DataToRF[0]);
		eeprom_write_byte(&eprom+0x101, DataToRF[1]);
		eeprom_write_byte(&eprom+0x102, DataToRF[2]);
		eeprom_write_byte(&eprom+0x103, DataToRF[3]);
		eeprom_write_byte(&eprom+0x104, DataToRF[4]);
		eeprom_write_byte(&eprom+0x105, DataToRF[5]);
		eeprom_write_byte(&eprom+0x106, DataToRF[6]);
		eeprom_write_byte(&eprom+0x107, DataToRF[7]);
		eeprom_write_byte(&eprom+0x108, DataToRF[8]);
		eeprom_write_byte(&eprom+0x109, DataToRF[9]);
	EEcount=0;
	}
*/
//	if ((ADCSRA & 0x20) == 0 )	ADCSRA |= (1<<ADSC);			//����� ���
	TCNT0 = 0;					//������������� �������� �������
}
