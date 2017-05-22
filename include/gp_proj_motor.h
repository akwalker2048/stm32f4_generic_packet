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
#define MOTOR_START           0x10
#define MOTOR_STOP            0x11
#define MOTOR_QUERY_PID_LIMS  0x12
#define MOTOR_SET_PID_LIMS    0x13


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

#endif

