#ifndef GP_PROJ_THERMAL_H
#define GP_PROJ_THERMAL_H

#include "generic_packet.h"

#define LEPTON_VOSPI_FRAME_SIZE 164
#define LEPTON_PIXELS_PER_FRAME  80

/* List of packet types */
#define THERMAL_LEPTON_FRAME 0x00


typedef enum {LEPTON_VALID_FRAME, LEPTON_DISCARD_FRAME, LEPTON_CRC_FAIL_FRAME} FrameType;

typedef struct {
   FrameType type;
   uint8_t number;
   uint16_t crc;
   uint8_t data[LEPTON_VOSPI_FRAME_SIZE];
   uint16_t pixels[LEPTON_PIXELS_PER_FRAME];
} VOSPIFrame;

uint8_t create_thermal_lepton_frame(GenericPacket *packet, VOSPIFrame *frame);
uint8_t extract_thermal_lepton_frame(GenericPacket *packet, VOSPIFrame *frame);
uint16_t vospi_crc_calculator(VOSPIFrame *frame);
uint8_t decode_thermal_lepton_frame(VOSPIFrame *frame);

#endif
