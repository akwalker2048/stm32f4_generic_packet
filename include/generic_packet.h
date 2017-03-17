#ifndef GENERIC_PACKET_H
#define GENERIC_PACKET_H

/* This code will be shared & compiled on both Linux based PC's and
 * STM32F4 ARM processors.  It should use standard C libraries and
 * struct use of stdint types so that it is portable.
 */
#include <stdint.h>

/* Define the Packet Structure.  This packet type should be very
 * versatile across a broad range of projects and applications.
 * If a particular application requires something special, then
 * a new or different packet structure should be used.  For
 * instance, if this structure has too much header overhead to
 * work in a very bandwidth intensive application, then a
 * different packet structure should be designed and used for that
 * application.
 */

/* ************************************************************* */
/* * Packet Structure                                          * */
/* ************************************************************* */
#define GP_LOC_START_BYTE       0
#define GP_LOC_PROJ_ID          1
#define GP_LOC_PROJ_SPEC        2
#define GP_LOC_NUM_BYTES        3
#define GP_LOC_CS               4
#define GP_LOC_DATA_START       5
#define GP_OVERHEAD_BYTES       6

/* ************************************************************* */
/* * Packet Defines                                            * */
/* ************************************************************* */
#define GP_START_BYTE          0x1B
#define GP_MAX_PACKET_LENGTH   0xFF
#define GP_MAX_PAYLOAD_LENGTH  (GP_MAX_PACKET_LENGTH - GP_OVERHEAD_BYTES)

/* ************************************************************* */
/* * Receive Packet States and Such                            * */
/* ************************************************************* */
typedef enum {GP_STATE_FIND_START,
              GP_STATE_GET_PROJ_ID,
              GP_STATE_GET_PROJ_SPEC,
              GP_STATE_GET_NUM_BYTES,
              GP_STATE_GET_CS,
              GP_STATE_GET_DATA,
              GP_STATE_CHECKSUM} GenericPacketState;

typedef enum {GP_CONTROL_INITIALIZE, GP_CONTROL_RUN} GenericPacketStateControl;

/* ************************************************************* */
/* * Packet Structure                                          * */
/* ************************************************************* */
typedef struct {
   uint8_t data_index;
   uint8_t packet_length;
   uint8_t packet_error;
   GenericPacketState gp_state;
   uint8_t gp[GP_MAX_PACKET_LENGTH];
} GenericPacket;

/* ************************************************************* */
/* * Project IDs                                               * */
/* ************************************************************* */
/* * These are major projects...sub packets can be defined     * */
/* * within the data payload within these major project        * */
/* * categories.                                               * */
/* ************************************************************* */
#define GP_PROJ_INVALID        0x00
#define GP_PROJ_UNIVERSAL      0x01
#define GP_PROJ_TIA            0x02
#define GP_PROJ_ANALOG         0x03
#define GP_PROJ_THERMAL        0x04
#define GP_PROJ_SONAR          0x05
#define GP_PROJ_CAMERA         0x06
#define GP_PROJ_MOTOR_BLDC     0x07
#define GP_PROJ_MOTOR_STEPPER  0x08
#define GP_PROJ_MOTOR_BRUSH    0x09

/* ************************************************************* */
/* * Function Error Codes                                      * */
/* ************************************************************* */
#define GP_SUCCESS                       0x00
#define GP_ERROR_UNDEF                   0x01
#define GP_ERROR_CHECKSUM_MISMATCH       0x02
#define GP_ERROR_PACKET_TOO_BIG          0x03
#define GP_ERROR_READ_OUT_OF_RANGE       0x04
#define GP_ERROR_DATA_INDEX_OUT_OF_RANGE 0x05
#define GP_ERROR_UNDEFINED_PACKET_STATE  0x06



/* ************************************************************* */
/* * Function Prototypes                                       * */
/* ************************************************************* */
uint8_t gp_calc_checksum(GenericPacket *packet, uint8_t *cs);
uint8_t gp_compare_checksum(GenericPacket *packet);
uint8_t gp_add_checksum(GenericPacket *packet);
uint8_t gp_reset_packet(GenericPacket *packet);

/* Modify the header. */
uint8_t gp_add_proj(GenericPacket *packet, uint8_t pid, uint8_t pspec);
/* Get the header info. */
uint8_t gp_get_proj(GenericPacket *packet, uint8_t *pid, uint8_t *pspec);

/* Add data to the payload. */
uint8_t gp_add_uint8(GenericPacket *packet, uint8_t byte);
uint8_t gp_add_uint16(GenericPacket *packet, uint16_t chomp);
uint8_t gp_add_uint32(GenericPacket *packet, uint32_t word);
uint8_t gp_add_float32(GenericPacket *packet, float fpd);
/* Get data from the payload. */
uint8_t gp_get_uint8(GenericPacket *packet, uint8_t *byte);
uint8_t gp_get_uint16(GenericPacket *packet, uint16_t *chomp);
uint8_t gp_get_uint32(GenericPacket *packet, uint32_t *word);
uint8_t gp_get_float32(GenericPacket *packet, float *fpd);
uint8_t gp_set_data_index(GenericPacket *packet, uint8_t data_index);

#endif
