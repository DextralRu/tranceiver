/**
    @file    gun.config.h
    @author  Белоглазов В.А. ОАО "НПО РусБИТех", ЦСИ
    @date    01.03.2015
    @brief   Файл конфигурации исполнительного устройства имитатора
    В данном заголовочном файле описаны основные константы, необходимые для работы программы при первоначальном включении.
**/


#define GUNTYPE 				0

#define SPUSK_FIRE_VALUE 			0x58	//показание АЦП "момент спуска"
#define SPUSK_START_VALUE 			0xB0	//показание АЦП "начало нажатия на спуск"
#define PLANK_MIN_VALUE 			20	//показание АЦП для прицельной планки (датчика пока нет. Обработки пока нет.)
#define PLANK_MAX_VALUE 			200	//показание АЦП для прицельной планки (датчика пока нет. Обработки пока нет.)
//#define KLAPAN_ON_TIME				35	//время, в течении которого будет открыт пневмоклапан (программная реализация выстрела) 
//#define	KLAPAN_OFF_TIME 			60	//время, в течении которого будет закрыт пневмоклапан (программная реализация выстрела). 
#define KLAPAN_ON_TIME				20	//время, в течении которого будет открыт пневмоклапан (программная реализация выстрела) 
#define	KLAPAN_OFF_TIME 			35	//время, в течении которого будет закрыт пневмоклапан (программная реализация выстрела). 
							//суммарно эти параметры формируют темп стрельбы
#define MAXAMMOINCARTRAGE			30	//максимальное кол-во патрон в одном магазине
#define MAXCARTRAGE				10	//максимальное кол-во магазинов


#include "lib/cc1101/include/wr_settings.h"	//подключение заголовков для работы с CC1101
#include "lib/cc1101/include/rd_reg.h"		//подключение заголовков для работы с CC1101
#include "lib/cc1101/include/rd_burst_reg.h"	//подключение заголовков для работы с CC1101
#include "lib/cc1101/include/send_pkt.h"	//подключение заголовков для работы с CC1101
#include "lib/spi/spi.h"			//подключение заголовков для работы с SPI
#include "lib/l3g4200d/l3g4200d.h"              //подключение заголовков для работы с трехосевым гироскопом

#include "functions/variables.c"		//подключение файла с описанием переменных
#include "functions/wdt.c"                      //подключение файла с функцией Сторожевого таймера
#include "functions/gyro.c"			//подключение файла с функциями для работы с гироскопом
#include "functions/timer1ms.c"                 //подключение файла с функциями для работы 1мс интервального таймера
#include "functions/cc_int.c"			//подключение файла с функциями инициальзации CC1101
#include "functions/adc_int.c"			//подключение файла с функциями для работы АЦП
#include "functions/striker.c"			//подключение файла с функциями для работы с датчиком "урарник"
#include "functions/init_timers.c"		//подключение файла с функциями инициализации таймеров
#include "functions/firmmode.c"			//подключение файла с функцией проверки служебных сочетаний