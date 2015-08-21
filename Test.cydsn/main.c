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
void servo_control();
int main()
{
    struct Servo servot;
    servot.max_rotational_degree =180;
    servot.servo = SERVO_1A;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    init();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   
    for(;;)
   // servo_test(3,servot);
   servo_control();
    //motor_test();
   //i2c_test();
    
}
void init()
{
    EN_B_PWM_Start();
    EN_A_PWM_Start();
    Servo_A_Start();
    Servo_B_Start();
    I2C_Start();
    UART_Start();
    HMC5883L_Config();
}
void servo_test(int duration,struct Servo s1)
{  
    int pos =0;
    int i;
    int num;
    char buffer [50];
    for(i= 0; i <=duration; i++)
    {
    
        for(pos = 0; pos <= 180; pos = pos +10)
        {
            set_position((double)pos, &s1);
            num = sprintf(buffer, "Bearing: %d \n\r",(int) (s1.position));
            UART_PutArray( (uint8 *) buffer, (uint8)num);
            CyDelay(100);
        }
        for(pos = 180; pos >= 0; pos = pos -10)
        {
            set_position((double)pos, &s1);
            num = sprintf(buffer, "Bearing: %d \n\r",(int) (s1.position));
            UART_PutArray( (uint8 *) buffer, (uint8)num);
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
 
    char buffer[60];
    int num;
    UART_PutString("Test I2C \n\r");
   // HMC5883L_Config();
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
void servo_control()
{
    double pos = 0;
    char buffer[50];
    struct Servo pan;
    pan.max_rotational_degree =180;
    pan.servo = SERVO_1A;
    int num;
    for(;;)
    {   
        pos =0;
        for(num = 0; num < 10; num++)
        {
            pos = pos + (double) get_bearing();
            
        }
        pos = pos /10;
        num = sprintf(buffer, "Bearing: %d \n\r",(int) (pos*1));
        UART_PutArray( (uint8 *) buffer, (uint8)num);
        if(pos > pan.max_rotational_degree)
        {
          pos = pos/2;
        }
        set_position(pos,&pan);
        num = sprintf(buffer, "Bearing: %d \n\r",(int) (pos*1));
        //UART_PutArray((uint8 *) buffer, (uint8)num);
    }
    
}
/* [] END OF FILE */
