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

void set_position(uint16 position, struct Servo *s)
{
    uint16 temp;
    if(s->max_rotational_degree <= position)
    {
        s->position = position;
    }
    else
    {
        s->position = s->max_rotational_degree;
    }
    switch(s->servo)
    {
        case SERVO_1A:
            temp = ((265*s->position)/9)+1800;
            Servo_A_WriteCompare1((uint16) temp);
            break;
        case SERVO_1B:
            temp = ((50*s->position)/3+3000);
            Servo_A_WriteCompare2((uint16) temp);
            break;
        case SERVO_2A:
            temp =((50*s->position)/3+3000);
            Servo_B_WriteCompare1((uint16) temp);
            break;
        case SERVO_2B:
            temp = ((50*s->position)/3+3000);
            Servo_B_WriteCompare2((uint16) temp);
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
