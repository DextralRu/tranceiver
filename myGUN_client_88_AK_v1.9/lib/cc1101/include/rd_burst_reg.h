#include <avr/io.h>
#include <util/crc16.h> 
#include "reg_rf.h"
#include "../../../config.h"

uint16_t Read_Burst_Reg(uint8_t addr, uint8_t *buffer, uint8_t count);
