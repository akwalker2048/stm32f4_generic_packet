#include "gp_circular_buffer.h"

/* Initialize the Generic Packet Circular Buffer
 *  Note:
 *   +All other functions assume that this was called initially.
 *   +Trust the caller to make sure gp_array_size is correct for gp_array
 */
uint8_t gpcb_initialize(GenericPacketCircularBuffer *gpcbs, GenericPacket *gp_array, uint32_t gp_array_size)
{
   uint8_t retval;

   gpcbs->gpcb = gp_array;
   gpcbs->gpcb_size = gp_array_size;
   gpcbs->gpcb_head = 0;
   gpcbs->gpcb_head_temp = 0;
   gpcbs->gpcb_tail = 0;

   retval = gpcb_increment_temp_head(gpcbs);
   if(retval == GP_CIRC_BUFFER_SUCCESS)
   {
      retval = gp_receive_byte(0x00, GP_CONTROL_INITIALIZE, &(gpcbs->gpcb[gpcbs->gpcb_head_temp]));
      if(retval != GP_CIRC_BUFFER_SUCCESS)
      {
         return GP_CIRC_BUFFER_INITIALIZATION_FAILURE;
      }
   }
   else
   {
      return GP_CIRC_BUFFER_INITIALIZATION_FAILURE;
   }

   return GP_CIRC_BUFFER_SUCCESS;

}

/* Increment "temp_head".
 *  Note:  This should be done and "temp_head" should be used to point to a
 *         packet that is currently being written.  The real head should not
 *         be incremented until the packet is complete and ready for tail to
 *         be incremented and the packet used.
 */
uint8_t gpcb_increment_temp_head(GenericPacketCircularBuffer *gpcbs)
{
   uint32_t temp_temp_head;

   /* Store this in the event that we cannot increment head_temp. */
   temp_temp_head = gpcbs->gpcb_head_temp;

   /* Increment head_temp. */
   gpcbs->gpcb_head_temp++;
   if(gpcbs->gpcb_head_temp >= gpcbs->gpcb_size)
   {
      gpcbs->gpcb_head_temp = 0;
   }

   /* Check to make sure we didn't catch the tail. */
   if(gpcbs->gpcb_head_temp == gpcbs->gpcb_tail)
   {
      /* If we did...don't increment...and let the caller know. */
      gpcbs->gpcb_head_temp = temp_temp_head;
      return GP_CIRC_BUFFER_ERROR_HEAD_CAUGHT_TAIL;
   }

   return GP_CIRC_BUFFER_SUCCESS;

}

/* Increment "head".
 *  Note:  This is simply setting "head" to "temp_head" once the packet has been
 *         completely formed.
 */
uint8_t gpcb_increment_head(GenericPacketCircularBuffer *gpcbs)
{

   /* This should always be safe...because we didn't increment head_temp unless
    * it was OK to do so...and buffer rollover was handled there as well...
    */
   gpcbs->gpcb_head = gpcbs->gpcb_head_temp;

   return GP_CIRC_BUFFER_SUCCESS;

}

/* Increment "tail". */
uint8_t gpcb_increment_tail(GenericPacketCircularBuffer *gpcbs)
{
   uint32_t temp_tail;

   /* Store this in the event that we caught the head. */
   temp_tail = gpcbs->gpcb_tail;

   gpcbs->gpcb_tail++;
   if(gpcbs->gpcb_tail >= gpcbs->gpcb_size)
   {
      gpcbs->gpcb_tail = 0;
   }

   /* Did we catch the head?  Check here is greater than because we can read the
    * current head value because we don't increment it until it is ready to
    * read.  Notify the caller that we need to hang tight until the head is
    * incremented.
    */
   if(gpcbs->gpcb_tail > gpcbs->gpcb_head)
   {
      gpcbs->gpcb_tail = temp_tail;
      return GP_CIRC_BUFFER_ERROR_TAIL_CAUGHT_HEAD;
   }

   return GP_CIRC_BUFFER_SUCCESS;

}

/* Convenience function for receiving generic packet bytes when using the
 * Circular Buffer.
 */
uint8_t gpcb_receive_byte(uint8_t byte, GenericPacketCircularBuffer *gpcbs)
{
   uint8_t retval;

   retval = gp_receive_byte(byte, GP_CONTROL_RUN, &(gpcbs->gpcb[gpcbs->gpcb_head_temp]));
   if(retval == GP_CHECKSUM_MATCH)
   {
      /* We are done receiving a good packet...go ahead and increment head so
       * that it can be handled.  In this case, GP_CHECKSUM_MATCH will be
       * returned so that the caller will know that a packet is available.
       * Otherwise...if the caller is also just polling gpcb_increment_tail()
       * then they will know that another packet is available.
       */
      gpcb_increment_head(gpcbs);
      /* Now increment the next temp_head so that we can start receiving the
       * next packet.
       */
      gpcb_increment_temp_head(gpcbs);
   }

   /* This function will just return the underlying gp_receive_byte status for now. */
   return retval;

}
