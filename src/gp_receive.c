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
#ifdef PC_DEBUG_ON
         /* printf("retval = %u\n", retval); */
#endif
         return retval;
      }
      gp_packet->gp_state = GP_STATE_FIND_START;
      gpsc = GP_CONTROL_RUN;
   }

   if(gpsc == GP_CONTROL_RUN)
   {
#ifdef PC_DEBUG_ON
      /* printf("byte:  %u\t0x%2X\n", byte, byte); */
      /* printf("gp_packet->gp_state = %u\n", gp_packet->gp_state); */
#endif

      switch(gp_packet->gp_state)
      {
         case GP_STATE_INITIALIZE:
            retval = gp_reset_packet(gp_packet);
            if(retval != GP_SUCCESS)
            {
               return retval;
            }
            if(byte == GP_START_BYTE)
            {
               gp_packet->gp[GP_LOC_START_BYTE] = byte;
               gp_packet->gp_state = GP_STATE_GET_PROJ_ID;
#ifdef PC_DEBUG_ON
               /* printf("Go get project ID!\n"); */
#endif
            }
            else
            {
               gp_packet->gp_state = GP_STATE_FIND_START;
            }
            break;
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
            gp_packet->packet_length = byte + GP_OVERHEAD_BYTES;
            gp_packet->gp_state = GP_STATE_GET_CS;
            break;
         case GP_STATE_GET_CS:
            gp_packet->gp[GP_LOC_CS] = byte;
#ifdef PC_DEBUG_ON
            /* printf("Expecting %u bytes!\n", gp_packet->gp[GP_LOC_NUM_BYTES]); */
#endif
            if(gp_packet->gp[GP_LOC_NUM_BYTES] != 0)
            {
               gp_packet->data_index = 0;
               gp_packet->gp_state = GP_STATE_GET_DATA;
            }
            else
            {
               retval = gp_compare_checksum(gp_packet);
               gp_packet->gp_state = GP_STATE_INITIALIZE;
               if(retval == GP_SUCCESS)
               {
                  return GP_CHECKSUM_MATCH;
               }
               else
               {
                  return retval;
               }
            }
            break;
         case GP_STATE_GET_DATA:
            gp_packet->gp[GP_LOC_DATA_START + gp_packet->data_index] = byte;
            gp_packet->data_index++;
            if(gp_packet->data_index >= gp_packet->gp[GP_LOC_NUM_BYTES])
            {
               retval = gp_compare_checksum(gp_packet);
               gp_packet->gp_state = GP_STATE_INITIALIZE;
               if(retval == GP_SUCCESS)
               {
                  return GP_CHECKSUM_MATCH;
               }
               else
               {
                  return retval;
               }
            }
            if(gp_packet->data_index >= GP_MAX_PAYLOAD_LENGTH)
            {
               gp_packet->gp_state = GP_STATE_INITIALIZE;
               return GP_ERROR_PACKET_TOO_BIG;
            }
            break;
         default:
            return GP_ERROR_UNDEFINED_PACKET_STATE;
            break;
      }
   }

   return GP_SUCCESS;

}
