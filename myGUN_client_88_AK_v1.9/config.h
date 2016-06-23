/**
    @file    config.h
    @author  Белоглазов В.А. ОАО "НПО РусБИТех", ЦСИ
    @date    01.03.2015
    @brief   Файл конфигурации микроконтроллера ATMega88PA
    В данном заголовочном файле описаны основные настройки портов ввода/вывода для микроконтроллера ATMega88PA.
    Описаны как основное назначение и символьное обозначение портов, так и вспомогательные макросы управления
    этими портами.
**/

#ifndef CONFIG_H
#define CONFIG_H


//файл конфигурации микроконтроллера

#define F_CPU           16000000UL  //Частота кварцевого резонатора 18.43MHz
#define INTERRUPT_ONLY  { WDTCSR |= (1<<WDIE); WDTCSR &= ~(1<<WDE); }

#define CARTRAGEAKDDR   DDRC
#define CARTRAGEAKPIN   PINC
#define CARTRAGEAKPORT  PORTC
#define CARTRAGEAKDATA  PC1
#define GETCARTRAGEAK   ((1<<CARTRAGEAKDATA) & CARTRAGEAKPIN)
#define CARTRAGEAKINIT  {CARTRAGEAKDDR &= ~(1<<CARTRAGEAKDATA); CARTRAGEAKPORT |= (1<<CARTRAGEAKDATA);}


#define STRIKERAKDDR    DDRC
#define STRIKERAKPIN    PINC
#define STRIKERAKPORT   PORTC
#define STRIKERAKDATA   PC2
#define STRIKERAKVECTOR PCINT10
#define STRIKERAKINT    PCIE1
#define STRIKERAKPCMSK  PCMSK1
#define STRIKERAKFUNC   PCINT1_vect
#define STRIKERAKINIT   {STRIKERAKDDR &= ~(1<<STRIKERAKDATA);STRIKERAKPORT |=(1<<STRIKERAKDATA);}
#define STRIKERAKENABLE {STRIKERAKDDR &= ~(1<<STRIKERAKDATA);STRIKERAKPORT |=(1<<STRIKERAKDATA); PCICR |= (1 << STRIKERAKINT);STRIKERAKPCMSK |= (1 << STRIKERAKVECTOR);}
#define STRIKERAKCLOSE  {STRIKERAKPCMSK &= ~(1 << STRIKERAKVECTOR);}
#define STRIKERAKOPEN   {STRIKERAKPCMSK |= (1 << STRIKERAKVECTOR);}
#define GETSTRIKERAK    ((1<<STRIKERAKDATA) & STRIKERAKPIN)

#define FUSEAKDDR       DDRC
#define FUSEAKPORT      PORTC
#define FUSEAKPIN       PINC
#define FUSEAKDATA      PC3
#define GETFUSEAK       !((1<<FUSEAKDATA) & FUSEAKPIN)
#define FUSEAKINIT      {FUSEAKDDR &= ~(1<<FUSEAKDATA); FUSEAKPORT |= (1<<FUSEAKDATA);}

#define SINGLEAKDDR     DDRD
#define SINGLEAKPIN     PIND
#define SINGLEAKPORT    PORTD
#define SINGLEAKDATA    PD2
#define GETSINGLEAK     ((1<<SINGLEAKDATA) & SINGLEAKPIN)
#define SINGLEAKINIT    {SINGLEAKDDR &= ~(1<<SINGLEAKDATA);SINGLEAKPORT |= (1<<SINGLEAKDATA);}

#define POWER5VDDR      DDRB
#define POWER5VPORT     PORTB
#define POWER5V         PB0
#define POWER5VINIT     {POWER5VDDR |= (1<<POWER5V);}
#define POWER5VON       {POWER5VPORT |= (1<<POWER5V);}
#define POWER5VOFF      {POWER5VPORT &= ~(1<<POWER5V);}

#define LASERAKDDR      DDRD
#define LASERAKPORT     PORTD
#define LASERAKDATA     PD6
#define LASERAKINIT     {LASERAKDDR |= (1<<LASERAKDATA);}
#define LASERAKON       {LASERAKPORT |= (1<<LASERAKDATA);}
#define LASERAKOFF      {LASERAKPORT &= ~(1<<LASERAKDATA);}

#define KLAPANAKDDR     DDRD
#define KLAPANAKPORT    PORTD
#define KLAPANAKDATA    PD5
#define KLAPANAKINIT    {KLAPANAKDDR |= (1<<KLAPANAKDATA);}
#define KLAPANAKON      {KLAPANAKPORT |= (1<<KLAPANAKDATA);}
#define KLAPANAKOFF     {KLAPANAKPORT &= ~(1<<KLAPANAKDATA);}

#define SPUSKAKADATA    ADC6        //обособленный вывод контроллера
#define POWERDATA       ADC7        //обособленный вывод контроллера

#define LED1DDR         DDRD
#define LED1PORT        PORTD
#define LED1            PD4
#define LED1INIT        {LED1DDR |=(1<<LED1);}
#define LED1ON          {LED1PORT |=(1<<LED1);}
#define LED1OFF         {LED1PORT &=~(1<<LED1);}
#define LED1RE          {LED1PORT ^=(1<<LED1);}

#define SPI_DDR         DDRB
#define SPI_PORT        PORTB
#define SPI_MOSI        PB3
#define SPI_MISO        PB4
#define SPI_SCK         PB5
#define SPI_SS          PB2
#define GDO0D           PB1
#define GDO0_PORT       PORTB
#define GDO0_DDR        DDRB
#define GDO0_PIN        PINB

#define i2c_PORT        PORTC
#define i2c_DDR         DDRC
#define i2c_SCL         PC5
#define i2c_SDA         PC4

#define GDO0ENABLE      {GDO0_DDR &= ~(1<<GDO0D);GDO0_PORT &=~(1<<GDO0D); PCICR |= (1 << PCIE0);PCMSK0 |= (1 << PCINT1);}
#define GDO0CLOSE       {PCICR &= ~(1 << PCIE0);PCMSK0 &= ~(1 << PCINT1);}
#define GDO0OPEN        {PCICR |= (1 << PCIE0);PCMSK0 |= (1 << PCINT1);}
#define GDO0            ((1<<GDO0D) & GDO0_PIN)


#define UNSETCS         SPI_PORT |= (1 << SPI_SS);
#define SETCS           SPI_PORT &= ~(1 << SPI_SS);

#define Hi(Int)         (uint8_t)(Int>>8)
#define Lo(Int)         (uint8_t)(Int)

#define CARTRADGEQTY    30
#define DataSizeFromRF  32
#define DataSizeToRF    10
#define ADDRESSSIZE     1
#define PCKSIZE         1
#define CRC16SIZE       2
#define RSSISIZE        2
#define PACKETSIZE      PCKSIZE+DataSizeFromRF+CRC16SIZE

#define EEPROM_SECTION  __attribute__ ((section (".eeprom")))

#endif //CONFIG_H
