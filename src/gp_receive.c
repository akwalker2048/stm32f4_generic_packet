#include "generic_packet.h"
#include "gp_receive.h"

uint8_t gp_receive_byte(uint8_t byte, GenericPacketStateControl gpsc, GenericPacket *gp_packet)
{
   uint8_t retval;

   if(gpsc == GP_CONTROL_INITIALIZE)
   {
      retval = gp_reset_packet(gp_packet);
      if(retval != GP_SUCCESS)
      {
         return retval;
      }
      gp_packet->gp_state = GP_STATE_FIND_START;
      gpsc == GP_CONTROL_RUN;
   }

   if(gpsc == GP_CONTROL_RUN)
   {
      switch(gp_packet->gp_state)
      {
         case GP_STATE_FIND_START:
            if(byte == GP_START_BYTE)
            {
               gp_packet->gp[GP_LOC_START_BYTE] = byte;
               gp_packet->gp_state = GP_STATE_GET_PROJ_ID;
            }
            break;
         case GP_STATE_GET_PROJ_ID:
            gp_packet->gp[GP_LOC_PROJ_ID] = byte;
            gp_packet->gp_state = GP_STATE_GET_PROJ_SPEC;
            break;
         case GP_STATE_GET_PROJ_SPEC:
            gp_packet->gp[GP_LOC_PROJ_SPEC] = byte;
            gp_packet->gp_state = GP_STATE_GET_NUM_BYTES;
            break;
         case GP_STATE_GET_NUM_BYTES:
            gp_packet->gp[GP_LOC_NUM_BYTES] = byte;
            gp_packet->gp_state = GP_STATE_GET_CS;
            break;
         case GP_STATE_GET_CS:
            gp_packet->gp[GP_LOC_CS] = byte;
            if(gp_packet->gp[GP_LOC_NUM_BYTES] != 0)
            {
               gp_packet->data_index = 0;
               gp_packet->gp_state = GP_STATE_GET_DATA;
            }
            else
            {
               gp_packet->gp_state = GP_STATE_CHECKSUM;
            }
            break;
         case GP_STATE_GET_DATA:
            gp_packet->gp[GP_LOC_DATA_START + gp_packet->data_index] = byte;
            gp_packet->data_index++;
            if(gp_packet->data_index >= gp_packet->gp[GP_LOC_NUM_BYTES])
            {
               retval = gp_compare_checksum(gp_packet);
               gp_packet->gp_state = GP_STATE_FIND_START;
               return retval;
            }
            break;
         default:
            return GP_ERROR_UNDEFINED_PACKET_STATE;
            break;
      }
   }

}
