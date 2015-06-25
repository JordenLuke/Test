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
#include "HMC5883L.h"
#include "motordriver.h"
#include "Servo_Driver.h"

void init();
void servo_test(int duration,struct Servo s1);
void uart_test();
void i2c_test();
int main()
{
   CyGlobalIntEnable; /* Enable global interrupts. */
init();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uart_test();
    for(;;);
}
void init()
{
    //EN_B_PWM_Start();
    //EN_A_PWM_Start();
    //Servo_A_Start();
    //Servo_B_Start();
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
    uint16 num;
    int i =0;
    char *buff;
    UART_ClearRxBuffer();
    UART_PutString("Hello World. This is an UART TEST can you see me.");
    UART_PutString("Please send me data and I will Echo it back");
    for(;;)
    {
        while(UART_GetRxBufferSize() == 1){
        UART_WriteTxData(UART_GetChar());
        }
    }
}
void i2c_test();
/* [] END OF FILE */
