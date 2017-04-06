
#include "gp_proj_analog.h"

uint8_t create_analog_voltage(GenericPacket *packet, uint8_t analog_packet_type, float voltage)
{
   FloatConv fc;

   /*   1.  Reset so we are starting with a fresh packet. */
   gp_reset_packet(packet);
   /*   2.  Add header information.  */
   gp_add_proj(packet, GP_PROJ_ANALOG, analog_packet_type);
   /*   3.  Add data of all types. */
   fc.fval = voltage;
   gp_add_uint32(packet, fc.ival);
   /*   4.  Add the checksum so that we are ready to "send". */
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_analog_voltage(GenericPacket *packet, float *voltage)
{
   FloatConv fc;

   gp_set_data_index(packet, 0);
   gp_get_uint32(packet, &(fc.ival));
   *voltage = fc.fval;

   return GP_SUCCESS;
}
