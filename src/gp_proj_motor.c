
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
