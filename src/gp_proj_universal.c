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
