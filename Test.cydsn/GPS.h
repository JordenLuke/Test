/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef GPS_H
#define GPS_H
#include <project.h>

struct GPGGA {

    uint32 UTC_time;
    int    Latitude;
    char   Indicator;
   

};
    
#endif
/* [] END OF FILE */
