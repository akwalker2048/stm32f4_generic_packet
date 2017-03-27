#include <stdio.h>
#include <stdint.h>

#include "generic_packet.h"
#include "gp_receive.h"
#include "gp_proj_universal.h"

#define GIT_CODEVER "some-git-code-version-8.8.8"

const char* blah = GIT_CODEVER;

int main(void)
{
   GenericPacket transmit_packet;
   GenericPacket receive_packet;
   uint8_t num_bytes;
   uint16_t ii;
   uint8_t retval;

   uint8_t byte;
   uint16_t chomp;
   uint32_t word;
   float fp;

   char codever[256];

   create_universal_test_packet(&transmit_packet, (uint8_t)0x12, (uint16_t)0x3456, (uint32_t)0x789ABCDE, (float)3.1415);
   /*  The packet would normally be sent here...but this
    *  test function does not cover that.  It is the
    *  responsibility of each implementation to provide
    *  their own send function.
    */

   /* Receive a test packet. */
   ii=0;
   retval = gp_receive_byte(transmit_packet.gp[ii], GP_CONTROL_INITIALIZE, &receive_packet);
   ii++;
   do{
      retval = gp_receive_byte(transmit_packet.gp[ii], GP_CONTROL_RUN, &receive_packet);
      ii++;
      if((retval == GP_CHECKSUM_MATCH)||(retval == GP_ERROR_CHECKSUM_MISMATCH))
      {
         ii = 257;
      }

   }while((ii<=GP_MAX_PACKET_LENGTH));

   if(retval != GP_CHECKSUM_MATCH)
   {
      printf("We must have gone through too many bytes without finding a valid packet!!!!\n");
      printf("Exiting!!!!\n");

      printf("\n\nCompare Packets!\n");
      printf("xmit\trcv\n");
      for(ii=0; ii<0xFF; ii++)
      {
         printf("0x%2X\t0x%2X\n", transmit_packet.gp[ii], receive_packet.gp[ii]);
      }

      printf("sizeof(float)\t%lu\n", sizeof(float));

      return 1;
   }
   else
   {
      retval = extract_universal_test_packet(&receive_packet, &byte, &chomp, &word, &fp);
      printf("Received Universal Test Packet!\n");
      printf("byte:  %u\t0x%2X\n", byte, byte);
      printf("chomp: %u\t0x%4X\n", chomp, chomp);
      printf("word:  %u\t0x%8X\n", word, word);
      printf("float: %g\n", fp);
   }


   /* create_universal_code_ver(&transmit_packet, "some-code-ver-2.4.3-256"); */
   create_universal_code_ver(&transmit_packet, GIT_REVISION);
   ii=0;
   retval = gp_receive_byte(transmit_packet.gp[ii], GP_CONTROL_INITIALIZE, &receive_packet);
   ii++;
   do{
      retval = gp_receive_byte(transmit_packet.gp[ii], GP_CONTROL_RUN, &receive_packet);
      ii++;
      if((retval == GP_CHECKSUM_MATCH)||(retval == GP_ERROR_CHECKSUM_MISMATCH))
      {
         ii = 257;
      }

   }while((ii<=GP_MAX_PACKET_LENGTH));

  if(retval != GP_CHECKSUM_MATCH)
   {
      printf("We must have gone through too many bytes without finding a valid packet!!!!\n");
      printf("Exiting!!!!\n");

      printf("\n\nCompare Packets!\n");
      printf("xmit\trcv\n");
      for(ii=0; ii<0xFF; ii++)
      {
         printf("0x%2X\t0x%2X\n", transmit_packet.gp[ii], receive_packet.gp[ii]);
      }

      printf("sizeof(float)\t%lu\n", sizeof(float));

      return 1;
   }
   else
   {
      retval = extract_universal_code_ver(&receive_packet, codever);
      printf("codever: %s\n", codever);
   }


   return 0;

}
