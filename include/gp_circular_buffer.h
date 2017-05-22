#include "generic_packet.h"
#include "gp_receive.h"

/* The circular buffer size can be increased or decreased based on your needs
 * by simply defining this from in your project.  For instance, you might
 * want this to be smaller for a microcontroller application and larger on the
 * PC/OS side...
 */
#ifndef GP_CIRC_BUFFER_SIZE
#define GP_CIRC_BUFFER_SIZE 16
#endif

#define GP_CIRC_BUFFER_SUCCESS                0x00
#define GP_CIRC_BUFFER_ERROR_TAIL_CAUGHT_HEAD 0x01
#define GP_CIRC_BUFFER_ERROR_HEAD_CAUGHT_TAIL 0x02
#define GP_CIRC_BUFFER_INITIALIZATION_FAILURE  0x03

/* ************************************************************* */
/* * GenericPacket Circular Buffer Structure                   * */
/* ************************************************************* */
typedef struct {
   GenericPacket gpcb[GP_CIRC_BUFFER_SIZE];
   uint32_t gpcb_head;
   uint32_t gpcb_head_temp;
   uint32_t gpcb_tail;
} GenericPacketCircularBuffer;


/* ************************************************************* */
/* * Circular Buffer Functions                                 * */
/* ************************************************************* */
uint8_t gpcb_initialize(GenericPacketCircularBuffer *gpcbs);
uint8_t gpcb_increment_temp_head(GenericPacketCircularBuffer *gpcbs);
uint8_t gpcb_increment_head(GenericPacketCircularBuffer *gpcbs);
uint8_t gpcb_increment_tail(GenericPacketCircularBuffer *gpcbs);
uint8_t gpcb_receive_byte(uint8_t byte, GenericPacketCircularBuffer *gpcbs);
