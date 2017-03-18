#ifndef GP_RECEIVE_H
#define GP_RECEIVE_H

#include "generic_packet.h"

uint8_t gp_receive_byte(uint8_t byte, GenericPacketStateControl gpsc, GenericPacket *gp_packet);

#endif
