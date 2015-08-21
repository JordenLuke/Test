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
#include "Servo_Driver.h"
#include"project.h"
/* this will right the new position of the servo
 * The PWM Block is used to create a pluse every 20ms.
 * The compare value is changed to change the duty cycle of the
 * PWM. The function will not exceed 2ms. The equations were found 
 * to map 0 - 180 from a compare value that = 1ms or 2ms. Using
 * The values as 3000 and 6000. The equations below came out.
 * This will have some fine tuning to get the right rotation due
 * to incorrect clocks. Move up and down the two points either
 * till the correct rotation is found. Every motor will be a bit 
 * different. The scales might be change to obtain better resolution. 
 */
void set_position(double position, struct Servo *s)
{
    uint16 temp;
    if(s->max_rotational_degree >= (uint16) position)
    {
        s->position = position;
    }
    else
    {
        s->position = (double) s->max_rotational_degree;
    }
    switch(s->servo)
    {
        case SERVO_1A:
        //gives better range for radio shack serov Cat no 2730766
            temp = (uint16)(((265*s->position)/9)+1800);
            Servo_A_WriteCompare1(temp);
            break;
        case SERVO_1B:
            temp = (uint16)(((50*s->position)/3)+3000);
            Servo_A_WriteCompare2(temp);
            break;
        case SERVO_2A:
            temp = (uint16)(((50*s->position)/3)+3000);
            Servo_B_WriteCompare1( temp);
            break;
        case SERVO_2B:
            temp = (uint16)(((50*s->position)/3+3000));
            Servo_B_WriteCompare2(temp);
            break;    
    }
}
uint16 get_position(struct Servo *s)
{
    
    return s->position;   
}
void set_max_rotational_degree(uint16 value, struct Servo *s)
{
    s->max_rotational_degree = value;
}
uint16 get_max_rotational_degree(struct Servo *s)
{
    return s->max_rotational_degree;   
}
/* [] END OF FILE */
