/**
 * @file gp_proj_motor.c
 * @author Andrew K. Walker
 * @date 22 MAY 2017
 * @brief Functions to create and extract all GP_PROJ_MOTOR packets.
 *
 * @todo Finish documenting all of the GenericPacket code.
 *
 */


#include "gp_proj_motor.h"



uint8_t create_motor_feedback(GenericPacket *packet, motor_feedback_t feedback)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_FEEDBACK);
   gp_add_float32(packet, feedback.time);
   gp_add_float32(packet, feedback.cmd);
   gp_add_float32(packet, feedback.msr);
   gp_add_float32(packet, feedback.err);
   gp_add_float32(packet, feedback.ierr);
   gp_add_float32(packet, feedback.derr);
   gp_add_float32(packet, feedback.out);
   gp_add_uint32(packet, feedback.encoder);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_feedback(GenericPacket *packet, motor_feedback_t *feedback)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, &(feedback->time));
   gp_get_float32(packet, &(feedback->cmd));
   gp_get_float32(packet, &(feedback->msr));
   gp_get_float32(packet, &(feedback->err));
   gp_get_float32(packet, &(feedback->ierr));
   gp_get_float32(packet, &(feedback->derr));
   gp_get_float32(packet, &(feedback->out));
   gp_get_uint32(packet, &(feedback->encoder));

   return GP_SUCCESS;

}


uint8_t create_motor_resp_position(GenericPacket *packet, float pos)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_RESP_POSITION);
   gp_add_float32(packet, pos);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_resp_position(GenericPacket *packet, float *pos)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, pos);

   return GP_SUCCESS;

}

uint8_t create_motor_set_pid(GenericPacket *packet, float p, float i, float d)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_SET_PID);
   gp_add_float32(packet, p);
   gp_add_float32(packet, i);
   gp_add_float32(packet, d);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_set_pid(GenericPacket *packet, float *p, float *i, float *d)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, p);
   gp_get_float32(packet, i);
   gp_get_float32(packet, d);

   return GP_SUCCESS;

}


uint8_t create_motor_query_pid(GenericPacket *packet)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_QUERY_PID);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_query_pid(GenericPacket *packet, float *p, float *i, float *d)
{

   return GP_SUCCESS;

}


uint8_t create_motor_resp_pid(GenericPacket *packet, float p, float i, float d)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_RESP_PID);
   gp_add_float32(packet, p);
   gp_add_float32(packet, i);
   gp_add_float32(packet, d);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_resp_pid(GenericPacket *packet, float *p, float *i, float *d)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, p);
   gp_get_float32(packet, i);
   gp_get_float32(packet, d);

   return GP_SUCCESS;

}

uint8_t create_motor_start(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_START);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_start(GenericPacket *packet)
{
   return GP_SUCCESS;
}

uint8_t create_motor_stop(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_STOP);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_stop(GenericPacket *packet)
{
   return GP_SUCCESS;
}

/* MOTOR_TMC260_SET_DRVCTRL create and extract functions. */
/* MOTOR_TMC260_QUERY_DRVCTRL create and extract functions. */
/* MOTOR_TMC260_RESP_DRVCTRL create and extract functions. */
/* MOTOR_TMC260_SET_CHOPCONF create and extract functions. */
/* MOTOR_TMC260_QUERY_CHOPCONF create and extract functions. */
/* MOTOR_TMC260_RESP_CHOPCONF create and extract functions. */
/* MOTOR_TMC260_SET_SMARTEN create and extract functions. */
/* MOTOR_TMC260_QUERY_SMARTEN create and extract functions. */
/* MOTOR_TMC260_RESP_SMARTEN create and extract functions. */
/* MOTOR_TMC260_SET_DRVCONF  create and extract functions. */
/* MOTOR_TMC260_QUERY_DRVCONF create and extract functions. */
/* MOTOR_TMC260_RESP_DRVCONF create and extract functions. */
/* MOTOR_TMC260_SET_SGCSCONF create and extract functions. */
/* MOTOR_TMC260_QUERY_SGCSCONF create and extract functions. */
/* MOTOR_TMC260_RESP_SGCSCONF create and extract functions. */

/* MOTOR_TMC260_QUERY_STATUS create and extract functions. */
uint8_t create_motor_tmc260_query_status(GenericPacket *packet, uint8_t status_type)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_QUERY_STATUS);
   gp_add_uint8(packet, status_type);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_query_status(GenericPacket *packet)
{
   return GP_SUCCESS;
}




/* MOTOR_TMC260_RESP_STATUS create and extract functions. */
/**
 *
 * @fn uint8_t create_motor_tmc260_resp_status(GenericPacket *packet, uint16_t position, uint16_t stall_guard, uint16_t current, uint8_t status_byte)
 * @brief Packet to pass TMC260 status back to host.
 * @param GenericPacket *packet - Pointer to the packet which will be filled with status data.
 * @param uint16_t position - Current step location as tracked by the driver.
 * @param uint16_t stall_guard - Current value of the stall guard as checked by the driver.
 * @param uint16_t current - Current value of the current measurment as tracked by the driver.
 * @param uint8_t status_byte - Each bit represents a different state of driver status.
 * @return GenericPacket return code.
 *
 * Not all of position, stall_guard, and current are returned every time.  It
 * depends on the type of status that was requested.
 */
uint8_t create_motor_tmc260_resp_status(GenericPacket *packet, uint16_t position, uint16_t stall_guard, uint16_t current, uint8_t status_byte)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_RESP_STATUS);
   gp_add_uint16(packet, position);
   gp_add_uint16(packet, stall_guard);
   gp_add_uint16(packet, current);
   gp_add_uint8(packet, status_byte);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_resp_status(GenericPacket *packet, uint16_t *position, uint16_t *stall_guard, uint16_t *current, uint8_t *status_byte)
{

   gp_set_data_index(packet, 0);
   gp_get_uint16(packet, position);
   gp_get_uint16(packet, stall_guard);
   gp_get_uint16(packet, current);
   gp_get_uint8(packet, status_byte);

   return GP_SUCCESS;
}
