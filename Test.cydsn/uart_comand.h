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
#include<project.h>
/*
*FORMATMOTORMESSAGE Create the message buffer to send to the motor
* controller
*   Byte 1: 255 (start byte 1)
*   Byte 2: 255 (start byte 2)
*   Byte 3: Message ID (value 0x02 = command)
*   Byte 4: Message Length (Number of bytes being sent, 9 in this case)
*   Byte 5: Command for left motor (0-255, 128 is stopped)
*   Byte 6: Command for right motor
*   Byte 7: Command for pan servo (0-180, degrees)
*   Byte 8: Command for tilt servo
*   Byte 9: Checksum (complement of sum of bytes)
*
* Copyright 2014 The MathWorks, Inc.
*/
struct Message_Bytes{
    uint8 message_id;
    uint8 message_len;
    uint8 left_motor;
    uint8 right_motor;
    uint8 pan;
    uint8 tilt;
    uint8 checksum;
 };
void uart_rx();
{
    
    
}
/* [] END OF FILE */
