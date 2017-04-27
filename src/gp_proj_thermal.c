#include "generic_packet.h"
#include "gp_proj_thermal.h"

uint8_t create_thermal_lepton_frame(GenericPacket *packet, VOSPIFrame *frame)
{
   uint8_t ii;

   /* Note:
    *  *frame must point to a uint8_t array that is LEPTON_VOSPI_FRAME_SIZE
    *  or else bad things may happen.
    */

   /* Build a test packet. */
   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_THERMAL, THERMAL_LEPTON_FRAME);
   /*   3.  Add data. */
   for(ii=0; ii<LEPTON_VOSPI_FRAME_SIZE; ii++)
   {
      gp_add_uint8(packet, frame->data[ii]);
   }
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_thermal_lepton_frame(GenericPacket *packet, VOSPIFrame *frame)
{
   uint8_t ii;

   /* Note:
    *  *frame must point to a uint8_t array that is LEPTON_VOSPI_FRAME_SIZE
    *  or else bad things may happen.
    */

   /* Check to make sure the size of the packet is correct. */
   if(packet->gp[GP_LOC_NUM_BYTES] != LEPTON_VOSPI_FRAME_SIZE)
   {
      return GP_ERROR_ILL_FORMED_PACKET;
   }
   else
   {
      gp_set_data_index(packet, 0);
      for(ii=0; ii<LEPTON_VOSPI_FRAME_SIZE; ii++)
      {
         gp_get_uint8(packet, &(frame->data[ii]));
      }
   }

   return GP_SUCCESS;
}

uint8_t decode_thermal_lepton_frame(VOSPIFrame *frame)
{

   uint16_t crc_calc;
   uint8_t ii, jj;

   /* Note:
    *  This function is higher level than what would typically be just
    *  creating and extracting packets.  But I thought it made sense
    *  to go here for now.
    */
   if(((frame->data[0]&0x0f) != 0x0f))
   {
#ifdef PC_DEBUG_ON
      printf("Valid Frame!!!!\n");
#endif
      frame->type = LEPTON_VALID_FRAME;
      frame->number = frame->data[1];
      frame->crc = (((uint16_t)frame->data[2])<<8) + frame->data[3];

      crc_calc = vospi_crc_calculator(frame);
      if(crc_calc != frame->crc)
      {
#ifdef PC_DEBUG_ON
         printf("  But...Crap...VOSPI CRC Fail!!!!\n");
#endif
         frame->type = LEPTON_CRC_FAIL_FRAME;
      }

      for(ii=0; ii<LEPTON_PIXELS_PER_FRAME; ii++)
      {
         jj=(ii*2)+4;
         frame->pixels[ii] = (((uint16_t)frame->data[jj])<<8) + (uint16_t)frame->data[jj+1];
      }

   }
   else
   {
#ifdef PC_DEBUG_ON
      printf("Discard Frame!!!!\n");
#endif
      frame->type = LEPTON_DISCARD_FRAME;
      for(ii=0; ii<LEPTON_PIXELS_PER_FRAME; ii++)
      {
         frame->pixels[ii] = 0x0000;
      }
   }

   return GP_SUCCESS;
}


uint16_t vospi_crc_calculator(VOSPIFrame *frame)
{
   /* x^16 + x^12 + x^5 + x^0
    *  Note that the highest bit is always assumed to be 1, so you do
    *  not need bigger than a 16 bit number to store it.  The 16th
    *  bit is checked before shifting it out of the register.
    */
   uint16_t crc_polynomial = 0x1021;
   /* Initialize the 16 bit CRC value to zero. */
   uint16_t crc = 0;

   uint8_t ii, jj;
   uint8_t byte;

   for(ii=0; ii<LEPTON_VOSPI_FRAME_SIZE; ii++)
   {
      /* Byte goes into the MSByte of CRC. */
      crc ^= (((uint16_t)(frame->data[ii]))<<8);

      for(jj=0; jj<8; jj++)
      {
         if((crc & 0x8000) != 0)
         {
            /* MSBit of CRC is 1. */
            crc = (crc<<1)^crc_polynomial;
         }
         else
         {
            crc = (crc<<1);
         }
      }
   }

   return crc;

}


uint8_t create_thermal_begin_lepton_image(GenericPacket *packet, uint16_t image_num, uint32_t time_ms)
{
   uint8_t ii;

   /* Build a test packet. */
   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_THERMAL, THERMAL_BEGIN_LEPTON_IMAGE);
   /*   3.  Add data. */
   gp_add_uint16(packet, image_num);
   gp_add_uint32(packet, time_ms);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_thermal_begin_lepton_image(GenericPacket *packet, uint16_t *image_num, uint32_t *time_ms)
{

   gp_set_data_index(packet, 0);
   gp_get_uint16(packet, image_num);
   gp_get_uint32(packet, time_ms);

   return GP_SUCCESS;
}

uint8_t create_thermal_end_lepton_image(GenericPacket *packet)
{

   /* Build a test packet. */
   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_THERMAL, THERMAL_END_LEPTON_IMAGE);
   /*   3.  No data to add. */
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_thermal_end_lepton_image(GenericPacket *packet)
{

   /* Nothing to do here.  Other than declare success because we got the packet. */

   return GP_SUCCESS;
}


uint8_t create_thermal_image_timeout(GenericPacket *packet)
{

   /* Build a test packet. */
   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_THERMAL, THERMAL_IMAGE_TIMEOUT);
   /*   3.  No data to add. */
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_thermal_image_timeout(GenericPacket *packet)
{

   /* Nothing to do here.  Other than declare success because we got the packet. */

   return GP_SUCCESS;
}


uint8_t create_thermal_cmd_grab_image(GenericPacket *packet)
{

   /* Build a test packet. */
   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_THERMAL, THERMAL_CMD_GRAB_IMAGE);
   /*   3.  No data to add. */
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_thermal_cmd_grab_image(GenericPacket *packet)
{

   /* Nothing to do here.  Other than declare success because we got the packet. */

   return GP_SUCCESS;
}
