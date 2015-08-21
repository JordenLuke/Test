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
#ifndef __SERVO_DRIVER_H__
#define __SERVO_DRIVER_H__
 

#include"project.h"
enum{
    SERVO_1A= 0x00, 
    SERVO_1B, 
    SERVO_2A, 
    SERVO_2B
};
struct Servo{
    uint16 max_rotational_degree;
    double position;
    uint8 servo;
};
void set_position(double position, struct Servo *s);
uint16 get_position(struct Servo *s);
void set_max_rotational_degree(uint16 value, struct Servo *s);
uint16 get_max_rotational_degree(struct Servo *s);

#endif
/* [] END OF FILE */
