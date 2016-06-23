/**
    @file    variables.c
    @author  Белоглазов В.А. ОАО "НПО РусБИТех", ЦСИ
    @date    01.03.2015
    @brief   Файл с описанием переменных имитатора
    В данном файле содержатся описания переменных имитатора. Все они являются глобальными т.к. это сильно сокращает использованием памяти микроконтроллера
    и экономит время на выделение локальных переменных и порождение их копий и экземпляров. Так же производится первоначальная инициализация некоторых переменных.
**/


uint8_t address=0;		//адрес устройства
uint8_t channel=0;		//частотный канал
uint8_t firststart;		//признак не первого старта
uint8_t EnableRF=0;		//заранее запрещаем работать радиомодулю (необходимо при включении)

uint8_t blinkmode=0;
uint16_t Vpower=0;		//напряжение питания
uint8_t	PowerCode=0x60;		//заряд аккумулятора в процентах
uint16_t Vspusk=0;		//напряжение спускового курка
uint16_t Vplank=0;		//напряжение прицельной планки
uint16_t Vgnd=0;			//напряжение НУЛЯ (служебное)
uint16_t Vtemp=0;		//пременная переменная для АЦП
uint8_t ADCmode=0;		//режим работы АЦП
uint8_t StrikerStartPosition;	//значение взведенного положения ударника

double ggx=0;
double ggy=0;
double ggz=0;

uint8_t cartrage=0;		//магазины
uint8_t grenade=0;		//гранаты
uint8_t powermode=0;
uint8_t ammo=0;			//боеприпасов в магазине
uint8_t PowerOn=0;              //имитатор включен/выключен
uint8_t LaserOn=0;		//лазер включен/выключен
uint8_t GameOn=0;		//участвуем или нет в занятии
uint16_t KlapanOnTime=KLAPAN_ON_TIME;	//время открытия клапана
uint16_t PauseTime=KLAPAN_OFF_TIME;      //время паузы клапана
uint16_t StartSpusk=SPUSK_START_VALUE;	//показания АЦП начала нажатия спускового крючка
uint16_t FireSpusk=SPUSK_FIRE_VALUE;	//показания АЦП производства выстрела
uint8_t minPlank=PLANK_MIN_VALUE;	//показания АЦП для минимального положения прицельной планки (нет датчика, нет обработчика)
uint8_t maxPlank=PLANK_MAX_VALUE;	//показания АЦП для максимального положения прицельной планки (нет датчика, нет обработчика)
uint16_t FireTimer;			//счетчик времени открытого клапана
uint16_t FireDelay;			//счетчик времени закрытого клапана

uint8_t DataFromRF[DataSizeFromRF];	//Пакет с командами который был принят правильно
uint8_t tmpDataFromRF[DataSizeFromRF];	//Пакет с командами который прилетел последним
uint8_t DataToRF[DataSizeToRF];		//Пакет с ответом

uint8_t SizeFromCC;		//длина, полученная с СС1101
uint8_t tmp;			//временная переменная
uint8_t command_flag;		//признак получения команды
uint16_t CRC16;			//то, что мы сами посчитаем
uint16_t tmpCRC16;		//то, что нам прислали
uint16_t tmpQ;			//место временного хранения RSSI и LQI

uint32_t timer=0;		//тут часики с шагом 1мс (для измерения времени нажатия спускового крючка)
uint8_t	 timerEnable=0;		//управление счетом времени нажатия спускового крючка
uint8_t FireStatus=0;		//состояние (такт) механизма произведения выстрела		
uint8_t lastFireStatus=0;
uint8_t AmmoInTrunk=0;		//патрон в патроннике
uint8_t FiredAmmoCount=0;	//кол-во произведенных выстрелов
uint8_t EventFire=0;		//событие выстрела
uint16_t CartrageStatus=0;      //временной показатель состояния магазина
uint8_t CartrageArray[31];     //содержимое магазинов
uint8_t Cartrages=MAXCARTRAGE;		//кол-во магазинов по умолчанию
uint8_t CartrageCurrent=1;	//номер текущего магазина
uint8_t CartrageTrigger=0;      //состояние магазина

signed int gxraw = 0;		//
signed int gyraw = 0;		//
signed int gzraw = 0;		//координатки исходные
double gx = 0;			//
double gy = 0;			//
double gz = 0;			//

float PositionX=0;		//
float PositionX2=0;		//
float angleX=0;			//
float PositionY=0;		//
float PositionY2=0;		//координатки расчетные
float angleY=0;			//
float PositionZ=0;		//
float PositionZ2=0;		//
float angleZ=0;			//

uint16_t EEcount=0;
uint16_t xx1=0x30;


uint8_t		eprom	EEPROM_SECTION  = 0;	//адрес однако в eeprom
