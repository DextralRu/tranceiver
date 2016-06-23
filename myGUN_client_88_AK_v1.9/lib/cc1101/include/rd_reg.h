#ifndef RDREG_H
#define RDREG_H
#include <avr/io.h>
#include "../../../config.h"
#include "reg_rf.h"
#include <util/delay.h>

uint8_t Read_Reg(uint8_t addr);

#endif
