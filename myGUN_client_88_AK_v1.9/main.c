/**
    @file    main.c
    @author  Белоглазов В.А. ОАО "НПО РусБИТех", ЦСИ
    @date    01.03.2015
    @brief   Файл основного тела программы имитатора
    В данном файле содержится основное тело программы. Сначала производится необходимое конфигурирование выводов микроконтроллера.
    После чего происходит определение ранее настроенных адреса и частотного канала.
    По завершению всех подготовительных операций запускается "бесконечный цикл" основного алгоритма.
**/

#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <delay.h>

#include "config.h"			//подключение файла конфигурации микроконтроллера
#include "gun.config.h"			//подключение файла конфигурации имитатора

               

//################################## MAIN ########################################### 
int main() {
LED1RE;
	EnableRF=0;
	CLKPR = (1 << CLKPCE); //разрешение перепрограммирования делителя (надо для некоторых чипов)
	CLKPR = 0x00;          //отключение делителя
//	_delay_ms(5000);
	FireStatus=0;		//статус выстрела "не стреляем"
	AmmoInTrunk=0;		//Нет патрона в патроннике
	command_flag=0;		//команд еще небыло
	CartrageStatus=20000;   //принимаем состояние магазина - снят более 2 секунд
//	CartrageTrigger=1;	//принимаем состояние магазина - извлечен
	CartrageTrigger=0;	//принимаем состояние магазина - установлен. Это не логично, но так "хотят" тверские
				//по правилам безопасности магазин должен устанавливаться непосредственно перед началом занятия, а не при включении
	CartrageCurrent=1;	//текущий магазин - пустой (служебный номер магазина)
	LaserOn=0;
	PowerOn=0;
	GameOn=0;

	CARTRAGEAKINIT;		//конфигурируем порт работы с датчиком "магазин АК"
	STRIKERAKINIT;		//конфигурируем порт работы с датчиком "ударник АК"
	FUSEAKINIT;		//конфигурируем порт работы с датчиком "предохранитель АК"
	SINGLEAKINIT;		//конфигурируем порт работы с датчиком "одиночный выстрел АК"
	LASERAKINIT;		//конфигурируем порт включения "лазер АК" 
	KLAPANAKINIT;		//конфигурируем порт включения "клапан АК" 
	LED1INIT;		//конфигурируем порт включения "светодиод" 
	POWER5VINIT;		//конфигурируем порт управления преобразователем напряжения 5В

	address=eeprom_read_byte(&eprom+00);	//вспомним, на каком адресе мы были
	channel=eeprom_read_byte(&eprom+0x01);	//ну и канал заодно
	firststart=eeprom_read_byte(&eprom+0x03);	//а тут примета не первого старта
	if ((address>0x07) || (address<0x00)) {eeprom_write_byte(&eprom+0x00, 0x00);address=0;}	//Впервые? Забыли? Потерли? значит 0
	if ((channel>0x07) || (channel<0x00)) {eeprom_write_byte(&eprom+0x01, 0x00);channel=0;}	//ну и канал заодно :)
	for (uint8_t i=0;i<10;i++) DataToRF[i]=0;//проведем зачистку буффера отправки
	DataToRF[0]=GUNTYPE;		//сразу запишем тип оружия

	CC_init();
	ADC_Init1();

	//########## осталось совсем чуть-чуть настроек #########################################
	GDO0ENABLE;			//Разрешаем ножке с GDO0 работать на вход
	GDO0OPEN;			//И включим обработку прерывания по этой ноге
	sei();				//разрешаем глобальные прерывания
	init_timer0();			//стартуем работу гироскопа
	init_timer2();			//и счетчика миллисекунд
	STRIKERAKENABLE;		//Включаем реакцию (прерывание) на ударник (иначе как мы узнаем о ручном "передергивании" затворной рамы?)
	//========================= НАЧИНАЕМ РАБОТУ ===================================

    	AmmoInTrunk=0;			//начальное положение - нет патрона в патроннике
	DataToRF[1]=0;

	FirmModeTest();			//проверка на служебнве сочетания

	init_timer0();			//стартуем работу АЦП
	init_timer2();			//и счетчика миллисекунд

	wdt_reset(); 			//погладим спящую собаку
    	wdt_enable(WDTO_1S);		//говорим ей сторожить 120 миллисекунд
    	INTERRUPT_ONLY; 		//разрешаем собачке вызывать прерывание. Иначе будет резет.


	while (1) {			//И вот он! Бесконечный цикл!
		    //_delay_us(1);
			if (PowerCode != 0x00) {
				if (PowerOn!=0) {POWER5VON;}	//Если была команда на включение - запустим преобразователь 5В
				else {POWER5VOFF;}		//Иначе стоим и экономим аккумулятор
			}
			else POWER5VOFF;

		    if (LaserOn!=0) {LASERAKON; DataToRF[3]|=(1<<7);}	//Если была команда на включение - запустим преобразователь 5В(лазер включен )
			else {LASERAKOFF;DataToRF[3]&=~(1<<7);}		//Иначе стоим и экономим аккумулятор ( лазер  отключен )

		   //Это для отладки. показывает наличие патрона в патроннике
//		    if (PowerOn==1) {LASERAKON;}
//			else {LASERAKOFF;}

		    if (AmmoInTrunk) {DataToRF[0] |= (1<<6);}	//Если патрон в патроннике - отметим это в пакете
			else {DataToRF[0] &= ~(1<<6);}		//И если его нет - тоже отметим

		    if (GETFUSEAK) {DataToRF[0] |= (1<<5);}	//Если стоим на предохранителе - отметим в пакете
			else {DataToRF[0] &= ~(1<<5);}		//И если нет - тоже отметим

		    //############### Процесс извлечения и установки магазина ####################################	
		    if ((GETCARTRAGEAK!=0) && (CartrageTrigger==0)) {	//Если извлекли совсем недавно
			CartrageStatus++;				//начнем считать это время
			_delay_us(1);
			if (CartrageStatus==20000) CartrageTrigger=1;	//Если уже давно вынут, принимаем состояние - извлечен
			};

		    if ((GETCARTRAGEAK==0) && (CartrageTrigger==1)) {   //Если Установлен совсем недавно
			CartrageStatus--;				//начинаем считать это время
			if (CartrageStatus==0) {			//время на установку исчерпано
			    CartrageTrigger=0;				//принимаем состояние - установлен
			    CartrageCurrent++;				//выбираем следующий номер магазина
				FiredAmmoCount=0;			//Сбросим кол-во произведенных выстрелов
				DataToRF[6]=0;
			    if (CartrageCurrent>MAXCARTRAGE) CartrageCurrent=0;	//А не привысили ли мы максимальный номер магазина?
			    if (CartrageCurrent>Cartrages) CartrageCurrent=0;	//А не превысили ли мы лимит выданных программой?
										//Если да, то встаем на пустой магазин!
			    DataToRF[1]|=CartrageCurrent;			//номер магазина в пакет
			    }
			};

			if (EnableRF==0) {
				if (GETCARTRAGEAK==0) 			//при первом включении определим магазин
					CartrageTrigger=0;
				else CartrageTrigger=1;
			}

		    if (CartrageTrigger==0)  {DataToRF[0] |= (1<<3);}	//отметим извлечение и установку магазина в пакете
			else {DataToRF[0] &= ~(1<<3);}

		    if (EventFire!=0) {DataToRF[1] |= (1<<7);}		//отметим состояние "производится выстрел"
			else {DataToRF[1] &= ~(1<<7);}

		    if (GETSINGLEAK==0) {DataToRF[1] |= (1<<5);}		//отметим состояние "одиночный" темп стрельбы
			else {DataToRF[1] &= ~(1<<5);}

		DataToRF[2]=(DataToRF[2] & 0xE0) | CartrageArray[1];

		if ((command_flag) && (powermode==0)) {				//ой! команда прилитела!
		uint8_t offset=(address<<2);			//вычисляем наш кусочек команды из всего массива
//############################################################################################################################
		if (DataFromRF[offset+0] & 0x80) {		//СМЕНА АДРЕСА?
			address=(DataFromRF[offset+0] & 0x7);	//выделили и запомнили новый адрес
			eeprom_write_byte(&eprom+0x00, address);//и в eeprom впихнули
			}
//############################################################################################################################
		if (DataFromRF[offset+0] & 0x40) {		//СМЕНА КАНАЛА?
			channel=(DataFromRF[offset+0] & 0x7);	//выделили и запомнили новый канал
			eeprom_write_byte(&eprom+0x01, channel);//и в eeprom впихнули
			}
//############################################################################################################################
			PowerOn=(DataFromRF[offset+0] & 0x20);	//МЕНЯ ВКЛЮЧИЛИ!=0 ИЛИ ВЫКЛЮЧИЛИ==0
//############################################################################################################################
			if (PowerOn!=0) {LaserOn=(DataFromRF[offset+0] & 0x10);}	//ЛАЗЕР ВКЛЮЧИЛИ!=0 ИЛИ ВЫКЛЮЧИЛИ==0
			if ((LaserOn!=0) && (PowerOn!=0)) {LASERAKON;DataToRF[3]|=(1<<7);}
			    else {LASERAKOFF;DataToRF[3]&=~(1<<7);}
//############################################################################################################################
			if (PowerOn!=0) {GameOn=(DataFromRF[offset+0] & 0x08);}	//Упражнение ВКЛЮЧИЛИ!=0 ИЛИ ВЫКЛЮЧИЛИ==0
//############################################################################################################################
		uint8_t command=(DataFromRF[offset+1] & 0xE0);			//определение команды
//############################################################################################################################
		if (command==0x20) {						//команда загрузки количество обойм, патронов, гранат
			cartrage=(DataFromRF[offset+1] & 0x1F); 
			ammo=(DataFromRF[offset+2] & 0x1F);
			if (cartrage<=10) {Cartrages=cartrage;CartrageCurrent=1;}
			if (ammo<=MAXAMMOINCARTRAGE) {
				CartrageArray[1]=ammo;
				}
			}
				    
		if (command==0xE0) {						//аналог команды 0х20, только с предварительным сбросом всего
			FiredAmmoCount=0;
			AmmoInTrunk=0;
			CartrageCurrent=0;
			CartrageArray[1]=0;
			Cartrages=0;
			DataToRF[6]=FiredAmmoCount;				//кол-во выстрелов в пакет
			DataToRF[2]=(DataToRF[2] & 0xE0) | CartrageArray[1];	//кол-во патрон в пакет
			DataToRF[1]|=CartrageCurrent;				//номер магазина в пакет
			cartrage=(DataFromRF[offset+1] & 0x1F);			//это выполнение команды 0x20 
			ammo=(DataFromRF[offset+2] & 0x1F);
			if (cartrage<=10) {Cartrages=cartrage;CartrageCurrent=1;}
			if (ammo<=MAXAMMOINCARTRAGE) {
				CartrageArray[1]=ammo;
				}
			}
		if (command==0x40) {StartSpusk=(DataFromRF[offset+2]); minPlank=(DataFromRF[offset+3]);}//мин знач с датч. спускового крючка и приц. планки
		if (command==0x60) {FireSpusk=(DataFromRF[offset+2]); maxPlank=(DataFromRF[offset+3]);}	//макс знач с датч спускового крючка и приц. планки
		if (command==0x80) KlapanOnTime=DataFromRF[offset+3];					//время открытия клапана
		if (command==0xA0) PauseTime=DataFromRF[offset+3];					//время между открытиями клапана (темп стрельбы)
		command_flag=0;										//команда была обработана, снимаем флаг
		}
	EnableRF=1;	//some changes were made
	}// основной бесконечный цикл
}
