#include <stdint.h>
#include <stdio.h>

#include "generic_packet.h"


/* ************************************************************* */
/* * gp_calc_checksum                                          * */
/* ************************************************************* */
/* * This really only need to be an internal function.  There  * */
/* * is no reason that this one should need to be called from  * */
/* * outside.  Really just making one function that both the   * */
/* * compare and add checksum functions can call.              * */
/* ************************************************************* */
uint8_t gp_calc_checksum(GenericPacket *packet, uint8_t *cs)
{
   uint8_t ii;
   uint8_t lcs;

   lcs = 0;
   for(ii=0; ii<packet->packet_length; ii++)
   {
      /* Note, the checksum byte itself is not included. */
      if(ii != GP_LOC_CS)
      {
         lcs += packet->gp[ii];
      }
   }

   lcs = ~lcs + 1;
   *cs = lcs;

   return GP_SUCCESS;
}


/* ************************************************************* */
/* * gp_compare_checksum                                       * */
/* ************************************************************* */
/* * Calculate the checksum and compare it to the checksum     * */
/* * byte.  Use to verify a received packet.  Note, this does  * */
/* * not modify the checksum byte!                             * */
/* ************************************************************* */
uint8_t gp_compare_checksum(GenericPacket *packet)
{
   uint8_t calc_cs;
   uint8_t retval;

   retval = gp_calc_checksum(packet, &calc_cs);
   if(retval != GP_SUCCESS)
   {
      return GP_ERROR_UNDEF;
   }

   if(packet->gp[GP_LOC_CS] != calc_cs)
   {
      printf("Checksum...Expected %u...Got %u\n", packet->gp[GP_LOC_CS], calc_cs);
      return GP_ERROR_CHECKSUM_MISMATCH;
   }

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_add_checksum                                           * */
/* ************************************************************* */
/* * This function will calculate the checksum and then write  * */
/* * the checksum byte.  It is used right before sending the   * */
/* * packet.  Note that the function to actually send and      * */
/* * receive the packet must be written for the specific       * */
/* * hardware that is implementing it.  That function looks    * */
/* * different depending on whether it's on the micro or pc.   * */
/* ************************************************************* */
uint8_t gp_add_checksum(GenericPacket *packet)
{
   uint8_t calc_cs;
   uint8_t retval;

   retval = gp_calc_checksum(packet, &calc_cs);
   packet->gp[GP_LOC_CS] = calc_cs;

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_reset_packet                                           * */
/* ************************************************************* */
/* * This function deleted any data in the packet and gets     * */
/* * ready to start loading it with the next packet.   You     * */
/* * might be able to do a quick reset not actually blowing    * */
/* * all the data away.  But that might also be less safe.  It * */
/* * would assume that you would overwrite all of the old data * */
/* * when filling the next packet.                             * */
/* *                                                           * */
/* * Note that you must reset a packet before either reading   * */
/* * or creating a new one.                                    * */
/* ************************************************************* */
uint8_t gp_reset_packet(GenericPacket *packet)
{
   uint8_t ii;

   packet->data_index = 0;
   packet->packet_length = GP_OVERHEAD_BYTES;
   packet->packet_error = 0;
   packet->gp_state = GP_STATE_FIND_START;
   for(ii=0; ii<GP_MAX_PACKET_LENGTH; ii++)
   {
      packet->gp[ii] = 0x00;
   }
   packet->gp[GP_LOC_START_BYTE] = GP_START_BYTE;
   packet->gp[GP_LOC_PROJ_ID] = GP_PROJ_INVALID;
   packet->gp[GP_LOC_NUM_BYTES] = 0;

   return GP_SUCCESS;
}


/* ************************************************************* */
/* * gp_add_proj                                               * */
/* ************************************************************* */
/* * The project information is the only header information    * */
/* * that should be manually added.  The rest of the header    * */
/* * should be correctly set as long as the gp functions       * */
/* * gp_reset_packet, gp_add_*, and gp_add_checksum have been  * */
/* * used to create the packet.  If you manually inserted data * */
/* * and mucked things up...then it's your problem.            * */
/* ************************************************************* */
uint8_t gp_add_proj(GenericPacket *packet, uint8_t pid, uint8_t pspec)
{

   packet->gp[GP_LOC_PROJ_ID] = pid;
   packet->gp[GP_LOC_PROJ_SPEC] = pspec;

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_get_proj                                               * */
/* ************************************************************* */
uint8_t gp_get_proj(GenericPacket *packet, uint8_t *pid, uint8_t *pspec)
{

   *pid = packet->gp[GP_LOC_PROJ_ID];
   *pspec = packet->gp[GP_LOC_PROJ_SPEC];

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_add_uint8                                              * */
/* ************************************************************* */
/* * Fundamentally, all of the gp_add_* functions use this     * */
/* * function to add each element.  That means we can just use * */
/* * this one function to keep track of the data_index and     * */
/* * data_length bytes.                                        * */
/* ************************************************************* */
uint8_t gp_add_uint8(GenericPacket *packet, uint8_t byte)
{
   uint8_t write_index;

   /* We must check before we increment the length and index.  If
      these were already at the max...then we have already exceeded
      the max packet size.  Adding another byte would overrun the
      buffer...or in this case overwrite the first data element
      since we have capped it at uint8_t's. */
   if((packet->data_index >= GP_MAX_PAYLOAD_LENGTH)||(packet->packet_length >= GP_MAX_PACKET_LENGTH))
   {
      packet->packet_error = GP_ERROR_PACKET_TOO_BIG;
      return packet->packet_error;
   }
   write_index = GP_OVERHEAD_BYTES + packet->data_index;
   packet->gp[write_index] = byte;

   packet->data_index = packet->data_index + 1;
   packet->packet_length = packet->packet_length + 1;

   packet->gp[GP_LOC_NUM_BYTES] = packet->data_index;

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_add_uint16                                             * */
/* ************************************************************* */
uint8_t gp_add_uint16(GenericPacket *packet, uint16_t chomp)
{
   uint8_t retval;
   uint8_t big_byte, little_byte;

   big_byte = (uint8_t)((chomp>>8)&0xFF);
   little_byte = (uint8_t)(chomp&0xFF);

   retval = gp_add_uint8(packet, little_byte);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_add_uint8(packet, big_byte);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_add_uint32                                             * */
/* ************************************************************* */
uint8_t gp_add_uint32(GenericPacket *packet, uint32_t word)
{
   uint8_t retval;
   uint8_t little, big, bigger, biggest;

   biggest = (uint8_t)((word>>24)&0xFF);
   bigger = (uint8_t)((word>>16)&0xFF);
   big = (uint8_t)((word>>8)&0xFF);
   little = (uint8_t)(word&0xFF);

   retval = gp_add_uint8(packet, little);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_add_uint8(packet, big);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_add_uint8(packet, bigger);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_add_uint8(packet, biggest);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_add_float32                                            * */
/* ************************************************************* */
/* * Unlike with stdint.h, I haven't seen anything to define a * */
/* * float to be exactly 32 bits.  I believe that is the case  * */
/* * on both the STM32F4 and the linux box.  And double would  * */
/* * be 64...  However, this function may be suspect if that   * */
/* * assumption doesn't hold true.                             * */
/* ************************************************************* */
uint8_t gp_add_float32(GenericPacket *packet, float fpd)
{
   uint8_t retval;
   FloatConv fc;

   fc.fval = fpd;

   printf("gp_add_float32\t%g\t%u\n", fc.fval, fc.ival);

   retval = gp_add_uint32(packet, fc.ival);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_get_uint8                                              * */
/* ************************************************************* */
/* * This function will read the next byte in the packet based * */
/* * on the data_index.  It will then point the index to the   * */
/* * next byte to be read.  This works as long as you read out * */
/* * the whole packet when it is received.  You will need to   * */
/* * manually set the index using the gp_set_data_index()      * */
/* * function if you wish to read chunks out of order.         * */
/* ************************************************************* */
uint8_t gp_get_uint8(GenericPacket *packet, uint8_t *byte)
{

   uint8_t read_index;

   read_index = GP_OVERHEAD_BYTES + packet->data_index;

   if(read_index >= (packet->gp[GP_LOC_NUM_BYTES] + GP_OVERHEAD_BYTES))
   {
      return GP_ERROR_READ_OUT_OF_RANGE;
   }
   if(packet->data_index >= GP_MAX_PAYLOAD_LENGTH)
   {
      return GP_ERROR_READ_OUT_OF_RANGE;
   }

   *byte = packet->gp[read_index];
   packet->data_index = packet->data_index + 1;

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_get_uint16                                             * */
/* ************************************************************* */
uint8_t gp_get_uint16(GenericPacket *packet, uint16_t *chomp)
{
   uint8_t retval;
   uint8_t big, little;

   retval = gp_get_uint8(packet, &little);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_get_uint8(packet, &big);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   *chomp = ((uint16_t)big<<8) + little;

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_get_uint32                                             * */
/* ************************************************************* */
uint8_t gp_get_uint32(GenericPacket *packet, uint32_t *word)
{
   uint8_t retval;
   uint8_t little, big, bigger, biggest;

   retval = gp_get_uint8(packet, &little);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_get_uint8(packet, &big);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_get_uint8(packet, &bigger);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   retval = gp_get_uint8(packet, &biggest);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }


   *word = ((uint32_t)biggest<<24) + ((uint32_t)bigger<<16) + ((uint32_t)big<<8) + little;

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_get_float32                                            * */
/* ************************************************************* */
uint8_t gp_get_float32(GenericPacket *packet, float *fpd)
{
   uint8_t retval;
   FloatConv fc;

   retval = gp_get_uint32(packet, &fc.ival);
   if(retval != GP_SUCCESS)
   {
      return retval;
   }

   *fpd = fc.fval;

   return GP_SUCCESS;
}

/* ************************************************************* */
/* * gp_set_data_index                                         * */
/* ************************************************************* */
uint8_t gp_set_data_index(GenericPacket *packet, uint8_t data_index)
{
   if((data_index >= (packet->gp[GP_LOC_NUM_BYTES] - 1)) || (packet->gp[GP_LOC_NUM_BYTES] == 0))
   {
      return GP_ERROR_DATA_INDEX_OUT_OF_RANGE;
   }

   packet->data_index = data_index;

   return GP_SUCCESS;

}
