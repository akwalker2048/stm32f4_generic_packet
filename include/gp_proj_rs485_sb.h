#ifndef GP_PROJ_RS485_SB_H
#define GP_PROJ_RS485_SB_H

#include "generic_packet.h"

/* Packets when you know only one thing is connected. */
#define RS485_SET_ADDRESS
#define RS485_QUERY_ADDRESS
#define RS485_RESP_ADDRESS

/* Packets when everyone is on the bus. All of these packets will have an
 * address as the first byte of the
 */
#define RS485_INITIATE_READINGS

/* Work need to be done on what the INFO is and how to configure it. */
/* Cannot SET_SENSOR_INFO, it will be programmed into the sensor itself. */
#define RS485_QUERY_SENSOR_INFO
#define RS485_RESP_SENSOR_INFO
/* SENSOR_INFO Defines
   -Locations/Pose:
    1) Fixed number of predefined locations in a single byte
    2) Full ROS pose message info...Point + Quaternion
    3) Something else
   -Type:
    1) SONAR, VCSEL, etc...
    2) PROXIMITY, TEMP, THERMAL, etc...
   -Number:
    1) A single micro out there could have multiple sensors attached.

*/
#define RS485_INITIATE_READING
#define RS485_QUERY_DATA
#define RS485_RESP_DATA

/* Do we need to tell the slaves about timeout values, or other communication
 * specific things?
 */
#define RS485_SETTINGS


#define RS485_ADDRESS_MAX_SLAVE     0xFC
#define RS485_ADDRESS_MASTER        0xFD
#define RS485_ADDRESS_CONFIGURATION 0xFE
#define RS485_ADDRESS_BROADCAST     0xFF

#endif
