#include <string.h>
#include "generic_packet.h"
#include "gp_proj_universal.h"

uint8_t create_universal_test_packet(GenericPacket *packet, uint8_t byte, uint16_t chomp, uint32_t word, float fp)
{

   /* Build a test packet. */
   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_TEST_PACKET);
   /*   3.  Add data of all types. */
   gp_add_uint8(packet, byte);
   gp_add_uint16(packet, chomp);
   gp_add_uint32(packet, word);
   gp_add_float32(packet, fp);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}


uint8_t extract_universal_test_packet(GenericPacket *packet, uint8_t *byte, uint16_t *chomp, uint32_t *word, float *fp)
{

   /* Pull data from a test packet.  Must be pulled in the same order it was put in...
    * ...unless you want to use the gp_set_data_index() function every time...
    */
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, byte);
   gp_get_uint16(packet, chomp);
   gp_get_uint32(packet, word);
   gp_get_float32(packet, fp);

   return GP_SUCCESS;

}

uint8_t create_universal_timestamp(GenericPacket *packet, uint32_t timestamp)
{

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_TIMESTAMP);
   /*   3.  Add data of all types. */
   gp_add_uint32(packet, timestamp);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_universal_timestamp(GenericPacket *packet, uint32_t *timestamp)
{

   gp_set_data_index(packet, 0);
   gp_get_uint32(packet, timestamp);

   return GP_SUCCESS;
}




uint8_t create_universal_ack(GenericPacket *packet)
{

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_ACK);
   /*   No data needed.  The "UNIVERSAL_ACK" is all we need.
        /*   3.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_universal_ack(GenericPacket *packet)
{

   return GP_SUCCESS;
}

uint8_t create_universal_code_ver(GenericPacket *packet, char *codever)
{
   uint8_t ii;
   size_t len;

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_CODE_VER);
   /*   3.  Add code version string. */
   /* len = strlen(codever); */
   len = 0;
   do{
      len++;
   }while((codever[len] != '\0')&&(len<255));

   if(len > GP_MAX_PAYLOAD_LENGTH)
   {
      len = GP_MAX_PAYLOAD_LENGTH;
   }

   for(ii=0; ii<len; ii++)
   {
      gp_add_uint8(packet, (uint8_t)codever[ii]);
   }

   /*   No data needed.  The "UNIVERSAL_ACK" is all we need.
        /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_universal_code_ver(GenericPacket *packet, char *codever)
{

   uint8_t len;
   uint8_t ii;

   /* Note:  The variable codever must already be allocated to a size of 256 bytes. */
   gp_set_data_index(packet, 0);
   /* How many bites are in the string? */
   len = packet->gp[GP_LOC_NUM_BYTES];
   if(len > GP_MAX_PAYLOAD_LENGTH)
   {
      len = GP_MAX_PAYLOAD_LENGTH;
   }

   for(ii=0; ii<len; ii++)
   {
      gp_get_uint8(packet, &(codever[ii]));
   }
   codever[len] = '\0';

   return GP_SUCCESS;
}


uint8_t create_universal_str(GenericPacket *packet, char *str)
{
   uint8_t ii;
   size_t len;

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_STRING);
   /*   3.  Add string. */
   len = 0;
   do{
      len++;
   }while((str[len] != '\0')&&(len<255));

   if(len > GP_MAX_PAYLOAD_LENGTH)
   {
      len = GP_MAX_PAYLOAD_LENGTH;
   }

   for(ii=0; ii<len; ii++)
   {
      gp_add_uint8(packet, (uint8_t)str[ii]);
   }

   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_universal_string(GenericPacket *packet, char *str)
{

   uint8_t len;
   uint8_t ii;

   /* Note:  The variable codever must already be allocated to a size of 256 bytes. */
   gp_set_data_index(packet, 0);
   /* How many bites are in the string? */
   len = packet->gp[GP_LOC_NUM_BYTES];
   if(len > GP_MAX_PAYLOAD_LENGTH)
   {
      len = GP_MAX_PAYLOAD_LENGTH;
   }

   for(ii=0; ii<len; ii++)
   {
      gp_get_uint8(packet, &(str[ii]));
   }
   str[len] = '\0';

   return GP_SUCCESS;
}

uint8_t create_universal_word(GenericPacket *packet, uint32_t word)
{

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_WORD);
   /*   3.  Add data of all types. */
   gp_add_uint32(packet, word);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_universal_word(GenericPacket *packet, uint32_t *word)
{

   gp_set_data_index(packet, 0);
   gp_get_uint32(packet, word);

   return GP_SUCCESS;
}


uint8_t create_universal_chomp(GenericPacket *packet, uint16_t chomp)
{

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_CHOMP);
   /*   3.  Add data of all types. */
   gp_add_uint16(packet, chomp);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_universal_chomp(GenericPacket *packet, uint16_t *chomp)
{

   gp_set_data_index(packet, 0);
   gp_get_uint16(packet, chomp);

   return GP_SUCCESS;
}


uint8_t create_universal_byte(GenericPacket *packet, uint8_t byte)
{

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_BYTE);
   /*   3.  Add data of all types. */
   gp_add_uint8(packet, byte);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_universal_byte(GenericPacket *packet, uint8_t *byte)
{

   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, byte);

   return GP_SUCCESS;
}



uint8_t create_universal_float(GenericPacket *packet, float flt)
{

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_UNIVERSAL, UNIVERSAL_FLOAT);
   /*   3.  Add data of all types. */
   gp_add_float32(packet, flt);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_universal_float(GenericPacket *packet, float *flt)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, flt);

   return GP_SUCCESS;
}
