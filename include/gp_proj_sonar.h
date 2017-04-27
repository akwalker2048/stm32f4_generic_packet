#ifndef GP_PROJ_SONAR_H
#define GP_PROJ_SONAR_H

#include "generic_packet.h"

#define SONAR_MAXBOT_SERIAL 0x00

uint8_t create_sonar_maxbot_serial(GenericPacket *packet, char *data);
uint8_t extract_sonar_maxbot_serial(GenericPacket *packet, uint8_t *inches);


#endif
