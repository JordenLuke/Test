/*******************************************************************************
* File Name: Servo_Out2A.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Servo_Out2A.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Servo_Out2A__PORT == 15 && ((Servo_Out2A__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Servo_Out2A_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void Servo_Out2A_Write(uint8 value) 
{
    uint8 staticBits = (Servo_Out2A_DR & (uint8)(~Servo_Out2A_MASK));
    Servo_Out2A_DR = staticBits | ((uint8)(value << Servo_Out2A_SHIFT) & Servo_Out2A_MASK);
}


/*******************************************************************************
* Function Name: Servo_Out2A_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Servo_Out2A_DM_STRONG     Strong Drive 
*  Servo_Out2A_DM_OD_HI      Open Drain, Drives High 
*  Servo_Out2A_DM_OD_LO      Open Drain, Drives Low 
*  Servo_Out2A_DM_RES_UP     Resistive Pull Up 
*  Servo_Out2A_DM_RES_DWN    Resistive Pull Down 
*  Servo_Out2A_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Servo_Out2A_DM_DIG_HIZ    High Impedance Digital 
*  Servo_Out2A_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Servo_Out2A_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Servo_Out2A_0, mode);
}


/*******************************************************************************
* Function Name: Servo_Out2A_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Servo_Out2A_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Servo_Out2A_Read(void) 
{
    return (Servo_Out2A_PS & Servo_Out2A_MASK) >> Servo_Out2A_SHIFT;
}


/*******************************************************************************
* Function Name: Servo_Out2A_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Servo_Out2A_ReadDataReg(void) 
{
    return (Servo_Out2A_DR & Servo_Out2A_MASK) >> Servo_Out2A_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Servo_Out2A_INTSTAT) 

    /*******************************************************************************
    * Function Name: Servo_Out2A_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Servo_Out2A_ClearInterrupt(void) 
    {
        return (Servo_Out2A_INTSTAT & Servo_Out2A_MASK) >> Servo_Out2A_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
