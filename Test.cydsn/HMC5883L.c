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
#include<HMC5883L.h>
#include<project.h>
#include "math.h"
/** Power on and prepare for general usage.
 * This will prepare the magnetometer with default settings, ready for single-
 * use mode (very low power requirements). Default settings include 8-sample
 * averaging, 15 Hz data output rate, normal measurement bias, a,d 1090 gain (in
 * terms of LSB/Gauss). Be sure to adjust any settings you need specifically
 * after initialization, especially the gain settings if you happen to be seeing
 * a lot of -4096 values (see the datasheet for mor information).
 */
void HMC5883L_Config()
{
    
	uint8 array[2];
  
    array [0] = HMC5883L_RA_CONFIG_A;
    array [1] = (HMC5883L_AVERAGING_8 << (HMC5883L_CRA_AVERAGE_BIT - HMC5883L_CRA_AVERAGE_LENGTH + 1)) |
        (HMC5883L_RATE_15     << (HMC5883L_CRA_RATE_BIT - HMC5883L_CRA_RATE_LENGTH + 1)) |
        (HMC5883L_BIAS_NORMAL << (HMC5883L_CRA_BIAS_BIT - HMC5883L_CRA_BIAS_LENGTH + 1));
    I2C_MasterSendStart(HMC5883L_ADDRESS, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(array[0]);
    I2C_MasterWriteByte(array[1]);
    I2C_MasterSendStop();
    
    array [0] = HMC5883L_RA_MODE;
    array [1] = HMC5883L_MODE_CONTINUOUS;
    
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(array[0]);
    I2C_MasterWriteByte(array[1]);
    I2C_MasterSendStop();
    
//    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
//    I2C_MasterWriteByte(0x02);
//    I2C_MasterWriteByte(0xA0);
//    I2C_MasterSendStop();
    
    CyDelay(67);
    
}

uint8 read_HMC5883L_reg(uint8 reg)
{
    uint8 value;
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(reg);
    I2C_MasterSendRestart(HMC5883L_ADDRESS, I2C_READ_XFER_MODE);
    value = I2C_MasterReadByte(I2C_ACK_DATA);
    
    return value;
}
//used to write to specific reg
uint8 write_HMC5883L_reg(uint8 reg, uint8 data)
{
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(reg);
    I2C_MasterWriteByte(data);
    I2C_MasterSendStop();
    return 0;
}
//This function only works in continous mode
void getHeading(int16 *x, int16 *y, int16*z)
{
    
   uint8 array[6];
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x03);
    CyDelay(6);
    I2C_MasterSendRestart(HMC5883L_ADDRESS, I2C_READ_XFER_MODE);
    array[0] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[1] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[2] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[3] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[4] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[5] = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    
    *x = (((int16)array[0]) << 8) | ((int16)array[1]);
    *y = (((int16)array[4]) << 8) | ((int16)array[5]);
    *z = (((int16)array[2]) << 8) | ((int16)array[3]);
}
int16_t getHeadingX()
{
    uint8 array[6];
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x03);
    CyDelay(6);
    I2C_MasterSendRestart(HMC5883L_ADDRESS, I2C_READ_XFER_MODE);
    array[0] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[1] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[2] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[3] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[4] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[5] = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    
    return((((uint16_t)array[0]) << 8) | ((uint16_t)array[1]));
}
int16_t getHeadingY()
{
    uint8 array[6];
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x03);
    CyDelay(6);
    I2C_MasterSendRestart(HMC5883L_ADDRESS, I2C_READ_XFER_MODE);
    array[0] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[1] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[2] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[3] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[4] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[5] = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
   
    return ((((uint16_t)array[4]) << 8) | ((uint16_t)array[5]));

}
int16_t getHeadingZ()
{
    uint8 array[6];
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x03);
    CyDelay(6);
    I2C_MasterSendRestart(HMC5883L_ADDRESS, I2C_READ_XFER_MODE);
    array[0] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[1] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[2] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[3] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[4] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[5] = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    
    return ((((uint16_t)array[2]) << 8) | ((uint16_t)array[3]));
}

uint16 get_HMC5883L_Data(int16 Data[])
{  
    uint8 array[6];
    I2C_MasterSendStart(HMC5883L_ADDRESS,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x03);
    CyDelay(6);
    I2C_MasterSendRestart(HMC5883L_ADDRESS, I2C_READ_XFER_MODE);
    array[0] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[1] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[2] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[3] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[4] = I2C_MasterReadByte(I2C_ACK_DATA);
    array[5] = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    
    Data[0] = (((int16)array[0]) << 8) | ((int16)array[1]);
    Data[2] = (((int16)array[2]) << 8) | ((int16)array[3]);
    Data[1] = (((int16)array[4]) << 8) | ((int16)array[5]);
    
    return 0;
}
//used to get the bearing in degrees 
double get_bearing()
{
    float bearing;
    int16 x;
    int16 y;
    int16 z;
    double cx;
    double cy;
    double cz;
    getHeading(&x,&y,&z);
    cx = (double) x * 10.0;
    cy = (double) y * 10.0;
    cz = (double) z * 10.0;
    
    bearing = atan2((cy),(cx));
    
    if(bearing <0)
        bearing +=  M_TWOPI;
    
    bearing = bearing *(180/M_PI);
    return bearing;
}
/* [] END OF FILE */
