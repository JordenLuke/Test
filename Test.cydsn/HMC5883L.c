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
    I2C_Start();
    
	uint8 array[2];
    array [0] = HMC5883L_RA_CONFIG_A;
    array [1] = (HMC5883L_AVERAGING_8 << (HMC5883L_CRA_AVERAGE_BIT - HMC5883L_CRA_AVERAGE_LENGTH + 1)) |
        (HMC5883L_RATE_15     << (HMC5883L_CRA_RATE_BIT - HMC5883L_CRA_RATE_LENGTH + 1)) |
        (HMC5883L_BIAS_NORMAL << (HMC5883L_CRA_BIAS_BIT - HMC5883L_CRA_BIAS_LENGTH + 1));
    I2C_MasterClearStatus();
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,2,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    array [0] = HMC5883L_RA_MODE;
    array [1] = HMC5883L_MODE_CONTINUOUS;
    I2C_MasterClearStatus();
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,2,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
}
uint8 read_HMC5883L_reg(uint8 reg)
{
    
    int16 value;
    uint8 array[2];
    array[0] = reg;
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,1,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    
    I2C_MasterReadBuf(HMC5883L_ADDRESS, array, 1,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    value = (uint16) array[0];
    return value;
}

uint8 write_HMC5883L_reg(uint8 reg, uint8 data)
{
    uint8 array[2];
    array[0] = reg;
    array[1] = data;
    
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,2,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    
    return 0;
}
uint8 testConnection();

//This function only works in continous mode
void getHeading(int16_t *x, int16_t *y, int16_t *z)
{
    
    uint8 array[6];
    array[0] = 0x06;
    union HMC5883L data;
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,1,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    
    I2C_MasterReadBuf(HMC5883L_ADDRESS,array,6,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    
    *data.array = *array;
    x = &data.Data.x;
    y = &data.Data.y;
    z = &data.Data.z;
    array[0] = 0x03;
    
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,1,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
}
int16_t getHeadingX()
{
    
    return 0;   
}
int16_t getHeadingY()
{
 
    return 0; 
}
int16_t getHeadingZ()
{
    return 0;    
}

uint16 get_HMC5883L_Data(union HMC5883L *Data)
{
    
    uint8 array[6];
    array[0] = 0x06;
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,1,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    
    I2C_MasterReadBuf(HMC5883L_ADDRESS,array,6,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    
    *Data->array = *array;
    array[0] = 0x03;
    
    I2C_MasterWriteBuf(HMC5883L_ADDRESS,array,1,I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    return I2C_MasterStatus();
}
/* [] END OF FILE */
