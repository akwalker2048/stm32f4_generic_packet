#ifndef GP_PROJ_ANALOG_H
#define GP_PROJ_ANALOG_H

#include "generic_packet.h"

/* List of analog packet types. */
#define ANALOG_VOLTAGE         0x00
#define ANALOG_BATTERY_VOLTAGE 0x01

uint8_t create_analog_voltage(GenericPacket *packet, uint8_t analog_packet_type, float voltage);
uint8_t extract_analog_voltage(GenericPacket *packet, float *voltage);

#endif
