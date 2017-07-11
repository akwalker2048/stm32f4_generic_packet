/**
 * @file gp_proj_motor.c
 * @author Andrew K. Walker
 * @date 22 MAY 2017
 * @brief Functions to create and extract all GP_PROJ_MOTOR packets.
 *
 * @todo Finish documenting all of the GenericPacket code.
 *
 */


#include "gp_proj_motor.h"



uint8_t create_motor_feedback(GenericPacket *packet, motor_feedback_t feedback)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_FEEDBACK);
   gp_add_float32(packet, feedback.time);
   gp_add_float32(packet, feedback.cmd);
   gp_add_float32(packet, feedback.msr);
   gp_add_float32(packet, feedback.err);
   gp_add_float32(packet, feedback.ierr);
   gp_add_float32(packet, feedback.derr);
   gp_add_float32(packet, feedback.out);
   gp_add_uint32(packet, feedback.encoder);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_feedback(GenericPacket *packet, motor_feedback_t *feedback)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, &(feedback->time));
   gp_get_float32(packet, &(feedback->cmd));
   gp_get_float32(packet, &(feedback->msr));
   gp_get_float32(packet, &(feedback->err));
   gp_get_float32(packet, &(feedback->ierr));
   gp_get_float32(packet, &(feedback->derr));
   gp_get_float32(packet, &(feedback->out));
   gp_get_uint32(packet, &(feedback->encoder));

   return GP_SUCCESS;

}


uint8_t create_motor_resp_position(GenericPacket *packet, float pos)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_RESP_POSITION);
   gp_add_float32(packet, pos);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_resp_position(GenericPacket *packet, float *pos)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, pos);

   return GP_SUCCESS;

}

uint8_t create_motor_set_pid(GenericPacket *packet, float p, float i, float d)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_SET_PID);
   gp_add_float32(packet, p);
   gp_add_float32(packet, i);
   gp_add_float32(packet, d);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_set_pid(GenericPacket *packet, float *p, float *i, float *d)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, p);
   gp_get_float32(packet, i);
   gp_get_float32(packet, d);

   return GP_SUCCESS;

}


uint8_t create_motor_query_pid(GenericPacket *packet)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_QUERY_PID);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_query_pid(GenericPacket *packet, float *p, float *i, float *d)
{

   return GP_SUCCESS;

}


uint8_t create_motor_resp_pid(GenericPacket *packet, float p, float i, float d)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_RESP_PID);
   gp_add_float32(packet, p);
   gp_add_float32(packet, i);
   gp_add_float32(packet, d);
   gp_add_checksum(packet);

   return GP_SUCCESS;

}

uint8_t extract_motor_resp_pid(GenericPacket *packet, float *p, float *i, float *d)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, p);
   gp_get_float32(packet, i);
   gp_get_float32(packet, d);

   return GP_SUCCESS;

}

uint8_t create_motor_start(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_START);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_start(GenericPacket *packet)
{
   return GP_SUCCESS;
}

uint8_t create_motor_stop(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_STOP);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_stop(GenericPacket *packet)
{
   return GP_SUCCESS;
}

uint8_t create_motor_home(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_HOME);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_home(GenericPacket *packet)
{
   return GP_SUCCESS;
}

uint8_t create_motor_set_position(GenericPacket *packet, float rad)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_SET_POSITION);
   gp_add_float32(packet, rad);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_set_position(GenericPacket *packet, float *rad)
{

   gp_set_data_index(packet, 0);
   gp_get_float32(packet, rad);

   return GP_SUCCESS;
}



/* MOTOR_TMC260_SET_DRVCTRL create and extract functions. */
uint8_t create_motor_tmc260_set_drvctrl_sdon(GenericPacket *packet, uint8_t intpol, uint8_t dedge, uint8_t mres)
{
   if(intpol > 1)
   {
      /* Default will be to disable step interpolation. */
      intpol = 0;
   }

   if(dedge > 1)
   {
      /* Default will be to step on both rising and falling edges. */
      dedge = 1;
   }

   if(mres > 8)
   {
      /* Default will be to step at 64ths... */
      mres = 2;
   }

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_SET_DRVCTRL_SDON);
   gp_add_uint8(packet, intpol);
   gp_add_uint8(packet, dedge);
   gp_add_uint8(packet, mres);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_set_drvctrl_sdon(GenericPacket *packet, uint8_t *intpol, uint8_t *dedge, uint8_t *mres)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, intpol);
   gp_get_uint8(packet, dedge);
   gp_get_uint8(packet, mres);

   return GP_SUCCESS;
}

/* MOTOR_TMC260_QUERY_DRVCTRL_SDON create and extract functions. */
uint8_t create_motor_tmc260_query_drvctrl_sdon(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_QUERY_DRVCTRL_SDON);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_query_drvctrl_sdon(GenericPacket *packet)
{
   return GP_SUCCESS;
}

/* MOTOR_TMC260_RESP_DRVCTRL_SDON create and extract functions. */
uint8_t create_motor_tmc260_resp_drvctrl_sdon(GenericPacket *packet, uint8_t intpol, uint8_t dedge, uint8_t mres)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_RESP_DRVCTRL_SDON);
   gp_add_uint8(packet, intpol);
   gp_add_uint8(packet, dedge);
   gp_add_uint8(packet, mres);
   gp_add_checksum(packet);

}

uint8_t extract_motor_tmc260_resp_drvctrl_sdon(GenericPacket *packet, uint8_t *intpol, uint8_t *dedge, uint8_t *mres)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, intpol);
   gp_get_uint8(packet, dedge);
   gp_get_uint8(packet, mres);

   return GP_SUCCESS;
}

/* MOTOR_TMC260_SET_CHOPCONF create and extract functions. */
uint8_t create_motor_tmc260_set_chopconf(GenericPacket *packet, uint8_t tbl, uint8_t chm, uint8_t rndtf, uint8_t hdec, uint8_t hend, uint8_t hstrt, uint8_t toff)
{
   if(tbl > 3)
   {
      /* Default will be to minimize blanking time. */
      tbl = 0;
   }

   if(chm > 1)
   {
      /* Default will be constant t_off. */
      chm = 1;
   }

   if(rndtf > 1)
   {
      /* Default will be fixed chopper off time... */
      rndtf = 0;
   }

   if(hdec > 3)
   {
      /* Default will be 0.  Default CHM == 1, so fast decay can terminate early and msb for fast decay is 0. */
      hdec = 0;
   }

   if(hend > 15)
   {
      /* Default will be 0.  Default CHM == 1, so this is a sine wave offset of 0. */
      hend = 0;

   }

   if(hstrt > 7)
   {
      /* Default will be 4.  Default CHM == 1, so this is fast deay time of 32*4 clocks. */
      hstrt = 4;
   }

   if(toff > 15)
   {
      /* Default will be 4.  Duration of slow decay phase. */
      toff = 4;
   }

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_SET_CHOPCONF);
   gp_add_uint8(packet, tbl);
   gp_add_uint8(packet, chm);
   gp_add_uint8(packet, rndtf);
   gp_add_uint8(packet, hdec);
   gp_add_uint8(packet, hend);
   gp_add_uint8(packet, hstrt);
   gp_add_uint8(packet, toff);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_set_chopconf(GenericPacket *packet, uint8_t *tbl, uint8_t *chm, uint8_t *rndtf, uint8_t *hdec, uint8_t *hend, uint8_t *hstrt, uint8_t *toff)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, tbl);
   gp_get_uint8(packet, chm);
   gp_get_uint8(packet, rndtf);
   gp_get_uint8(packet, hdec);
   gp_get_uint8(packet, hend);
   gp_get_uint8(packet, hstrt);
   gp_get_uint8(packet, toff);

   return GP_SUCCESS;
}

/* MOTOR_TMC260_QUERY_CHOPCONF create and extract functions. */
uint8_t create_motor_tmc260_query_chopconf(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_QUERY_CHOPCONF);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_query_chopconf(GenericPacket *packet)
{
   return GP_SUCCESS;
}

/* MOTOR_TMC260_RESP_CHOPCONF create and extract functions. */
uint8_t create_motor_tmc260_resp_chopconf(GenericPacket *packet, uint8_t tbl, uint8_t chm, uint8_t rndtf, uint8_t hdec, uint8_t hend, uint8_t hstrt, uint8_t toff)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_RESP_CHOPCONF);
   gp_add_uint8(packet, tbl);
   gp_add_uint8(packet, chm);
   gp_add_uint8(packet, rndtf);
   gp_add_uint8(packet, hdec);
   gp_add_uint8(packet, hend);
   gp_add_uint8(packet, hstrt);
   gp_add_uint8(packet, toff);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_resp_chopconf(GenericPacket *packet, uint8_t *tbl, uint8_t *chm, uint8_t *rndtf, uint8_t *hdec, uint8_t *hend, uint8_t *hstrt, uint8_t *toff)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, tbl);
   gp_get_uint8(packet, chm);
   gp_get_uint8(packet, rndtf);
   gp_get_uint8(packet, hdec);
   gp_get_uint8(packet, hend);
   gp_get_uint8(packet, hstrt);
   gp_get_uint8(packet, toff);

   return GP_SUCCESS;
}


/* MOTOR_TMC260_SET_SMARTEN create and extract functions. */
uint8_t create_motor_tmc260_set_smarten(GenericPacket *packet, uint8_t seimin, uint8_t sedn, uint8_t semax, uint8_t seup, uint8_t semin)
{
   if(seimin > 1)
   {
      /* Default will be 1/2 CS current setting. */
      seimin = 0;
   }

   if(sedn > 3)
   {
      /* Default will be that stallguard must be tripped 32 times before decrement. */
      sedn = 0;
   }

   if(semax > 15)
   {
      /* Default will be 2, defaut from TMC260 documentation. */
      semax = 2;
   }

   if(seup > 3)
   {
      /* Default will be a current increment size of 1. */
      seup = 0;
   }

   if(semin > 15)
   {
      /* Default is that this coolstep crap is DISABLED! */
      semin = 0;
   }

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_SET_SMARTEN);
   gp_add_uint8(packet, seimin);
   gp_add_uint8(packet, sedn);
   gp_add_uint8(packet, semax);
   gp_add_uint8(packet, seup);
   gp_add_uint8(packet, semin);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_set_smarten(GenericPacket *packet, uint8_t *seimin, uint8_t *sedn, uint8_t *semax, uint8_t *seup, uint8_t *semin)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, seimin);
   gp_get_uint8(packet, sedn);
   gp_get_uint8(packet, semax);
   gp_get_uint8(packet, seup);
   gp_get_uint8(packet, semin);

   return GP_SUCCESS;
}


/* MOTOR_TMC260_QUERY_SMARTEN create and extract functions. */
uint8_t create_motor_tmc260_query_smarten(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_QUERY_SMARTEN);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_query_smarten(GenericPacket *packet)
{
   return GP_SUCCESS;
}

/* MOTOR_TMC260_RESP_SMARTEN create and extract functions. */
uint8_t create_motor_tmc260_resp_smarten(GenericPacket *packet, uint8_t seimin, uint8_t sedn, uint8_t semax, uint8_t seup, uint8_t semin)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_RESP_SMARTEN);
   gp_add_uint8(packet, seimin);
   gp_add_uint8(packet, sedn);
   gp_add_uint8(packet, semax);
   gp_add_uint8(packet, seup);
   gp_add_uint8(packet, semin);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_resp_smarten(GenericPacket *packet, uint8_t *seimin, uint8_t *sedn, uint8_t *semax, uint8_t *seup, uint8_t *semin)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, seimin);
   gp_get_uint8(packet, sedn);
   gp_get_uint8(packet, semax);
   gp_get_uint8(packet, seup);
   gp_get_uint8(packet, semin);

   return GP_SUCCESS;
}


/* MOTOR_TMC260_SET_DRVCONF  create and extract functions. */
uint8_t create_motor_tmc260_set_drvconf(GenericPacket *packet, uint8_t tst, uint8_t slph, uint8_t slpl, uint8_t diss2g, uint8_t ts2g, uint8_t sdoff, uint8_t vsense, uint8_t rdsel)
{
   if(tst > 1)
   {
      /* Default...assume we aren't in test mode. */
      tst = 0;
   }

   if(slph > 3)
   {
      /* Default is minimum high side slope control. */
      slph = 0;
   }

   if(slpl > 3)
   {
      /* Default is minimum low side slope control. */
      slpl = 0;
   }

   if(diss2g > 1)
   {
      /* Default is short to ground protection enabled. */
      diss2g = 0;
   }

   if(ts2g > 3)
   {
      /* Default will be 3.2us short to ground timer. */
      ts2g = 0;
   }

   if(sdoff > 1)
   {
      /* Default is that we are in step and direction mode! */
      sdoff = 0;
   }

   if(vsense > 1)
   {
      /* Default is full scale sense resistor voltage is 305mV. */
      vsense = 0;
   }

   if(rdsel > 2)
   {
      /* Default is micrstep position for status feedback. */
      rdsel = 0;
   }

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_SET_DRVCONF);
   gp_add_uint8(packet, tst);
   gp_add_uint8(packet, slph);
   gp_add_uint8(packet, slpl);
   gp_add_uint8(packet, diss2g);
   gp_add_uint8(packet, ts2g);
   gp_add_uint8(packet, sdoff);
   gp_add_uint8(packet, vsense);
   gp_add_uint8(packet, rdsel);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_set_drvconf(GenericPacket *packet, uint8_t *tst, uint8_t *slph, uint8_t *slpl, uint8_t *diss2g, uint8_t *ts2g, uint8_t *sdoff, uint8_t *vsense, uint8_t *rdsel)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, tst);
   gp_get_uint8(packet, slph);
   gp_get_uint8(packet, slpl);
   gp_get_uint8(packet, diss2g);
   gp_get_uint8(packet, ts2g);
   gp_get_uint8(packet, sdoff);
   gp_get_uint8(packet, vsense);
   gp_get_uint8(packet, rdsel);

   return GP_SUCCESS;
}

/* MOTOR_TMC260_QUERY_DRVCONF create and extract functions. */
uint8_t create_motor_tmc260_query_drvconf(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_QUERY_DRVCONF);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_query_drvconf(GenericPacket *packet)
{
   return GP_SUCCESS;
}


/* MOTOR_TMC260_RESP_DRVCONF create and extract functions. */
uint8_t create_motor_tmc260_resp_drvconf(GenericPacket *packet, uint8_t tst, uint8_t slph, uint8_t slpl, uint8_t diss2g, uint8_t ts2g, uint8_t sdoff, uint8_t vsense, uint8_t rdsel)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_RESP_DRVCONF);
   gp_add_uint8(packet, tst);
   gp_add_uint8(packet, slph);
   gp_add_uint8(packet, slpl);
   gp_add_uint8(packet, diss2g);
   gp_add_uint8(packet, ts2g);
   gp_add_uint8(packet, sdoff);
   gp_add_uint8(packet, vsense);
   gp_add_uint8(packet, rdsel);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_resp_drvconf(GenericPacket *packet, uint8_t *tst, uint8_t *slph, uint8_t *slpl, uint8_t *diss2g, uint8_t *ts2g, uint8_t *sdoff, uint8_t *vsense, uint8_t *rdsel)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, tst);
   gp_get_uint8(packet, slph);
   gp_get_uint8(packet, slpl);
   gp_get_uint8(packet, diss2g);
   gp_get_uint8(packet, ts2g);
   gp_get_uint8(packet, sdoff);
   gp_get_uint8(packet, vsense);
   gp_get_uint8(packet, rdsel);

   return GP_SUCCESS;
}


/* MOTOR_TMC260_SET_SGCSCONF create and extract functions. */
uint8_t create_motor_tmc260_set_sgcsconf(GenericPacket *packet, uint8_t sfilt, uint8_t sgt, uint8_t cs)
{
   if(sfilt > 1)
   {
      /* Default...enable stallguard filtered mode. */
      sfilt = 1;
   }

   if(sgt > 127)
   {
      /* Default stallguard threshold. */
      sgt = 0x3F;
   }

   if(cs > 0x1F)
   {
      /* Default current scale. */
      cs = 0x12;
   }

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_SET_SGCSCONF);
   gp_add_uint8(packet, sfilt);
   gp_add_uint8(packet, sgt);
   gp_add_uint8(packet, cs);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_set_sgcsconf(GenericPacket *packet, uint8_t *sfilt, uint8_t *sgt, uint8_t *cs)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, sfilt);
   gp_get_uint8(packet, sgt);
   gp_get_uint8(packet, cs);

   return GP_SUCCESS;
}


/* MOTOR_TMC260_QUERY_SGCSCONF create and extract functions. */
uint8_t create_motor_tmc260_query_sgcsconf(GenericPacket *packet)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_QUERY_SGCSCONF);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_query_sgcsconf(GenericPacket *packet)
{
   return GP_SUCCESS;
}


/* MOTOR_TMC260_RESP_SGCSCONF create and extract functions. */
uint8_t create_motor_tmc260_resp_sgcsconf(GenericPacket *packet, uint8_t sfilt, uint8_t sgt, uint8_t cs)
{

   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_RESP_SGCSCONF);
   gp_add_uint8(packet, sfilt);
   gp_add_uint8(packet, sgt);
   gp_add_uint8(packet, cs);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_resp_sgcsconf(GenericPacket *packet, uint8_t *sfilt, uint8_t *sgt, uint8_t *cs)
{
   gp_set_data_index(packet, 0);
   gp_get_uint8(packet, sfilt);
   gp_get_uint8(packet, sgt);
   gp_get_uint8(packet, cs);

   return GP_SUCCESS;
}



/* MOTOR_TMC260_QUERY_STATUS create and extract functions. */
uint8_t create_motor_tmc260_query_status(GenericPacket *packet, uint8_t status_type)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_QUERY_STATUS);
   gp_add_uint8(packet, status_type);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_query_status(GenericPacket *packet)
{
   return GP_SUCCESS;
}




/* MOTOR_TMC260_RESP_STATUS create and extract functions. */
/**
 *
 * @fn uint8_t create_motor_tmc260_resp_status(GenericPacket *packet, uint16_t position, uint16_t stall_guard, uint16_t current, uint8_t status_byte)
 * @brief Packet to pass TMC260 status back to host.
 * @param GenericPacket *packet - Pointer to the packet which will be filled with status data.
 * @param uint16_t position - Current step location as tracked by the driver.
 * @param uint16_t stall_guard - Current value of the stall guard as checked by the driver.
 * @param uint16_t current - Current value of the current measurment as tracked by the driver.
 * @param uint8_t status_byte - Each bit represents a different state of driver status.
 * @return GenericPacket return code.
 *
 * Not all of position, stall_guard, and current are returned every time.  It
 * depends on the type of status that was requested.
 */
uint8_t create_motor_tmc260_resp_status(GenericPacket *packet, uint16_t position, uint16_t stall_guard, uint16_t current, uint8_t status_byte)
{
   gp_reset_packet(packet);
   gp_add_proj(packet, GP_PROJ_MOTOR, MOTOR_TMC260_RESP_STATUS);
   gp_add_uint16(packet, position);
   gp_add_uint16(packet, stall_guard);
   gp_add_uint16(packet, current);
   gp_add_uint8(packet, status_byte);
   gp_add_checksum(packet);

   return GP_SUCCESS;
}

uint8_t extract_motor_tmc260_resp_status(GenericPacket *packet, uint16_t *position, uint16_t *stall_guard, uint16_t *current, uint8_t *status_byte)
{

   gp_set_data_index(packet, 0);
   gp_get_uint16(packet, position);
   gp_get_uint16(packet, stall_guard);
   gp_get_uint16(packet, current);
   gp_get_uint8(packet, status_byte);

   return GP_SUCCESS;
}
