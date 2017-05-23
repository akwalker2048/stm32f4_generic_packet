#include "gp_proj_rs485_sb.h"

uint8_t create_rs485_query_sensor_info(GenericPacket *packet, uint8_t address)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_RS485_SB, RS485_QUERY_SENSOR_INFO);
   gp_add_uint8(packet, address);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_rs485_query_sensor_info(GenericPacket *packet, uint8_t *address)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, address);

   return GP_SUCCESS;
}


uint8_t create_rs485_resp_sensor_info(GenericPacket *packet, uint8_t address, uint8_t sensor_type, PoseIsh p)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_RS485_SB, RS485_RESP_SENSOR_INFO);
   gp_add_uint8(packet, address);
   gp_add_float32(packet, p.x);
   gp_add_float32(packet, p.y);
   gp_add_float32(packet, p.z);
   gp_add_float32(packet, p.roll);
   gp_add_float32(packet, p.pitch);
   gp_add_float32(packet, p.yaw);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}


uint8_t extract_rs485_resp_sensor_info(GenericPacket *packet, uint8_t *address, uint8_t *sensor_type, PoseIsh *p)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, address);
   gp_get_float32(packet, &(p->x));
   gp_get_float32(packet, &(p->y));
   gp_get_float32(packet, &(p->z));
   gp_get_float32(packet, &(p->roll));
   gp_get_float32(packet, &(p->pitch));
   gp_get_float32(packet, &(p->yaw));

   return GP_SUCCESS;
}
