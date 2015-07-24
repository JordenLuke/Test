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
#include <project.h>
#include <stdio.h>
#include <math.h>
#include "HMC5883L.h"
#include "motordriver.h"
#include "Servo_Driver.h"

void init();
void servo_test(int duration,struct Servo s1);
void uart_test();
void i2c_test();
void motor_test();
int main()
{
   CyGlobalIntEnable; /* Enable global interrupts. */
init();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   
    for(;;)
    //motor_test();
   i2c_test();
    
}
void init()
{
    EN_B_PWM_Start();
    EN_A_PWM_Start();
    Servo_A_Start();
    Servo_B_Start();
    I2C_Start();
    UART_Start();
}
void servo_test(int duration,struct Servo s1)
{  
    int16 pos;
    int i;
    for(i = 0; i < duration; i++)
    {
        for(pos = 0; pos <= 180; pos = pos +10)
        {
            set_position(pos, &s1);
            CyDelay(100);
        }
        for(pos = 180; pos >= 0; pos = pos -10)
        {
            set_position(pos, &s1);
            CyDelay(100);
        }
    }
}
void uart_test()
{   
   
    char buff = 0x01;
    UART_ClearRxBuffer();
    UART_PutString("Hello World. This is an UART TEST can you see me.");
    UART_PutString("Please send me data and I will Echo it back");
    for(;;)
    {
        while(UART_GetRxBufferSize() == 1 && buff != 'q'){
            buff = UART_GetChar();
            UART_WriteTxData(buff);
        }
    }
}
void i2c_test()
{
    double bearing = 0;
    struct HMC5883L_XYZ_Cord data;
    char buffer[60];
    int num;
    UART_PutString("Test I2C \n\r");
    HMC5883L_Config();
    for(;;){
        
        bearing = bearing + get_bearing();
        num = sprintf(buffer, "Bearing: %d \n\r",(int) (10*bearing));
        UART_PutArray( (uint8 *) buffer, (uint8)num);
        bearing =0;
        CyDelay(67);
    }
}
void motor_test()
{
    while(1){
        goBackward();
        CyDelay(1000);
        goForward();
        CyDelay(1000);
        goLeft();
        CyDelay(1000);
        goRight();
        CyDelay(1000);
    }
}
/* [] END OF FILE */
