#include <string.h>
#include <stdlib.h>
#include "generic_packet.h"
#include "gp_proj_sonar.h"

uint8_t create_sonar_maxbot_serial(GenericPacket *packet, char *data)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_SONAR, SONAR_MAXBOT_SERIAL);
   gp_add_uint8(packet, (uint8_t)data[0]);
   gp_add_uint8(packet, (uint8_t)data[1]);
   gp_add_uint8(packet, (uint8_t)data[2]);
   gp_add_uint8(packet, (uint8_t)data[3]);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}


uint8_t extract_sonar_maxbot_serial(GenericPacket *packet, uint8_t *inches)
{
   int tmp_inches;
   char maxbot_dist[4];

   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, &(maxbot_dist[0]));
   gp_get_uint8(packet, &(maxbot_dist[1]));
   gp_get_uint8(packet, &(maxbot_dist[2]));
   gp_get_uint8(packet, &(maxbot_dist[3]));

   tmp_inches = atoi(maxbot_dist);
   if(tmp_inches >= 255)
   {
      *inches = 255;
   }
   else
   {
      *inches = tmp_inches;
   }


   return GP_SUCCESS;
}
