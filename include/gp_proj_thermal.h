#ifndef GP_PROJ_THERMAL_H
#define GP_PROJ_THERMAL_H

#include "generic_packet.h"

#define LEPTON_VOSPI_FRAME_SIZE 164
#define LEPTON_PIXELS_PER_FRAME  80

/* List of packet types */
#define THERMAL_LEPTON_FRAME       0x00
#define THERMAL_BEGIN_LEPTON_IMAGE 0x01
#define THERMAL_END_LEPTON_IMAGE   0x02
#define THERMAL_IMAGE_TIMEOUT      0x03
#define THERMAL_CMD_GRAB_IMAGE     0x04
#define THERMAL_CMD_FREE_RUN       0x05
#define THERMAL_CMD_SOFTWARE_CTRL  0x06


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
uint8_t create_thermal_begin_lepton_image(GenericPacket *packet, uint16_t image_num, uint32_t time_ms);
uint8_t extract_thermal_begin_lepton_image(GenericPacket *packet, uint16_t *image_num, uint32_t *time_ms);
uint8_t create_thermal_end_lepton_image(GenericPacket *packet);
uint8_t extract_thermal_end_lepton_image(GenericPacket *packet);
uint8_t create_thermal_image_timeout(GenericPacket *packet);
uint8_t extract_thermal_image_timeout(GenericPacket *packet);
uint8_t create_thermal_cmd_grab_image(GenericPacket *packet);
uint8_t extract_thermal_cmd_grab_image(GenericPacket *packet);

#endif
