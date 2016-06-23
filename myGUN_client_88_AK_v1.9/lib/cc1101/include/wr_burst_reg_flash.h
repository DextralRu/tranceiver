#ifndef WRBURSTREGFLASH_H
#define WRBURSTREGFLASH_H
#include <avr/io.h>
#include <stdio.h>
#include <util/crc16.h>
#include "../../../config.h"
#include "reg_rf.h"

uint16_t Write_Burst_Reg_Flash(uint8_t addr, uint8_t *buffer, uint8_t count);

#endif
