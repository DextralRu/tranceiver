#ifndef WRREG_H
#define WRREG_H
#include <avr/io.h>
#include "../../../config.h"
#include "reg_rf.h"

void Write_Reg(uint8_t addr, uint8_t value);

#endif
