#ifndef WRSETTINGS_H
#define WRSETTINGS_H
#include <stdlib.h>
#include <avr/io.h>
#include "../../../config.h"
#include "wr_burst_reg_flash.h"
#include "wr_reg.h"

void Write_Settings(uint8_t Channel);
void Write_PA_Table(uint8_t value);

#endif
