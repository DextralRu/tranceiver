#ifndef SNDPKT_H
#define SNDPKT_H
#include <avr/io.h>
#include <util/delay.h>
#include "../../../config.h"
#include "reg_rf.h"
#include "wr_reg.h"
#include "wr_burst_reg_flash.h"
#include "wr_strobe.h"

void Send_Packet(uint8_t address, uint8_t *txBuffer, uint8_t datasize);

#endif