#ifndef GP_PROJ_UNIVERSAL_H
#define GP_PROJ_UNIVERSAL_H

#include "generic_packet.h"

/* List of packet types */
#define UNIVERSAL_TEST_PACKET 0x00
#define UNIVERSAL_TIMESTAMP   0x01
#define UNIVERSAL_ACK         0x02
#define UNIVERSAL_STRING      0x03
#define UNIVERSAL_BYTE        0x04
#define UNIVERSAL_CHOMP       0x05
#define UNIVERSAL_WORD        0x06
#define UNIVERSAL_FLOAT       0x07

uint8_t create_universal_test_packet(GenericPacket *packet, uint8_t byte, uint16_t chomp, uint32_t word, float fp);
uint8_t extract_universal_test_packet(GenericPacket *packet, uint8_t *byte, uint16_t *chomp, uint32_t *word, float *fp);

uint8_t create_universal_timestamp(GenericPacket *packet, uint32_t timestamp);
uint8_t extract_universal_timestamp(GenericPacket *packet, uint32_t *timestamp);

uint8_t create_universal_ack(GenericPacket *packet);
uint8_t extract_universal_ack(GenericPacket *packet);



#endif
