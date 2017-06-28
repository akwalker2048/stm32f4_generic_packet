#ifndef GP_PROJ_MOTOR_H
#define GP_PROJ_MOTOR_H

#include "generic_packet.h"

/* The first two... MOTOR_COMMAND and MOTOR_FEEDBACK are expected to include
 * a sizeable packet that covers the majority of things one would want to set
 * or monitor for a motor.  This provides a single set of overhead bytes but
 * a large amount of data.  Most of the rest of the packets are configured in
 * groups of three.  A packet for the host to query the driver.  A packet for
 * the host to set individual parameters.  And a packet for the driver to
 * respond with the current setting/value.
 */
#define MOTOR_COMMAND         0x00
#define MOTOR_FEEDBACK        0x01
#define MOTOR_QUERY_POSITION  0x02
#define MOTOR_SET_POSITION    0x03
#define MOTOR_RESP_POSITION   0x04
#define MOTOR_QUERY_VELOCITY  0x05
#define MOTOR_SET_VELOCITY    0x06
#define MOTOR_RESP_VELOCITY   0x07
#define MOTOR_QUERY_PID       0x08
#define MOTOR_SET_PID         0x09
#define MOTOR_RESP_PID        0x0A
#define MOTOR_START           0x0B
#define MOTOR_STOP            0x0C
#define MOTOR_QUERY_PID_LIMS  0x0D
#define MOTOR_SET_PID_LIMS    0x0E
/* TMC260 Commands */
#define MOTOR_TMC260_SET_DRVCTRL     0x20
#define MOTOR_TMC260_QUERY_DRVCTRL   0x21
#define MOTOR_TMC260_RESP_DRVCTRL    0x22
#define MOTOR_TMC260_SET_CHOPCONF    0x23
#define MOTOR_TMC260_QUERY_CHOPCONF  0x24
#define MOTOR_TMC260_RESP_CHOPCONF   0x25
#define MOTOR_TMC260_SET_SMARTEN     0x26
#define MOTOR_TMC260_QUERY_SMARTEN   0x27
#define MOTOR_TMC260_RESP_SMARTEN    0x28
#define MOTOR_TMC260_SET_DRVCONF     0x29
#define MOTOR_TMC260_QUERY_DRVCONF   0x2A
#define MOTOR_TMC260_RESP_DRVCONF    0x2B
#define MOTOR_TMC260_SET_SGCSCONF    0x2C
#define MOTOR_TMC260_QUERY_SGCSCONF  0x2D
#define MOTOR_TMC260_RESP_SGCSCONF   0x2E
#define MOTOR_TMC260_QUERY_STATUS    0x2F
#define MOTOR_TMC260_RESP_STATUS     0x30
/* TILT/Rotate Commands - Used regardless of tilt motor type. */
#define MOTOR_TILT_HOME  0x40
#define MOTOR_TILT_START 0x41
#define MOTOR_TILT_STOP  0x42


typedef struct {
   float time;
   float cmd;
   float msr;
   float err;
   float ierr;
   float derr;
   float out;
   uint32_t encoder;
} motor_feedback_t;

uint8_t create_motor_feedback(GenericPacket *packet, motor_feedback_t feedback);
uint8_t extract_motor_feedback(GenericPacket *packet, motor_feedback_t *feedback);

uint8_t create_motor_resp_position(GenericPacket *packet, float pos);
uint8_t extract_motor_resp_position(GenericPacket *packet, float *pos);

uint8_t create_motor_set_pid(GenericPacket *packet, float p, float i, float d);
uint8_t extract_motor_set_pid(GenericPacket *packet, float *p, float *i, float *d);

uint8_t create_motor_query_pid(GenericPacket *packet);
uint8_t extract_motor_query_pid(GenericPacket *packet, float *p, float *i, float *d);

uint8_t create_motor_resp_pid(GenericPacket *packet, float p, float i, float d);
uint8_t extract_motor_resp_pid(GenericPacket *packet, float *p, float *i, float *d);

uint8_t create_motor_start(GenericPacket *packet);
uint8_t extract_motor_start(GenericPacket *packet);

uint8_t create_motor_stop(GenericPacket *packet);
uint8_t extract_motor_stop(GenericPacket *packet);

uint8_t create_motor_tmc260_resp_status(GenericPacket *packet, uint16_t position, uint16_t stall_guard, uint16_t current, uint8_t status_byte);
uint8_t extract_motor_tmc260_resp_status(GenericPacket *packet, uint16_t *position, uint16_t *stall_guard, uint16_t *current, uint8_t *status_byte);

#endif

