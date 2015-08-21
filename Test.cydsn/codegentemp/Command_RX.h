/*******************************************************************************
* File Name: Command_RX.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Command_RX_H)
#define CY_ISR_Command_RX_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Command_RX_Start(void);
void Command_RX_StartEx(cyisraddress address);
void Command_RX_Stop(void);

CY_ISR_PROTO(Command_RX_Interrupt);

void Command_RX_SetVector(cyisraddress address);
cyisraddress Command_RX_GetVector(void);

void Command_RX_SetPriority(uint8 priority);
uint8 Command_RX_GetPriority(void);

void Command_RX_Enable(void);
uint8 Command_RX_GetState(void);
void Command_RX_Disable(void);

void Command_RX_SetPending(void);
void Command_RX_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Command_RX ISR. */
#define Command_RX_INTC_VECTOR            ((reg32 *) Command_RX__INTC_VECT)

/* Address of the Command_RX ISR priority. */
#define Command_RX_INTC_PRIOR             ((reg8 *) Command_RX__INTC_PRIOR_REG)

/* Priority of the Command_RX interrupt. */
#define Command_RX_INTC_PRIOR_NUMBER      Command_RX__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Command_RX interrupt. */
#define Command_RX_INTC_SET_EN            ((reg32 *) Command_RX__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Command_RX interrupt. */
#define Command_RX_INTC_CLR_EN            ((reg32 *) Command_RX__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Command_RX interrupt state to pending. */
#define Command_RX_INTC_SET_PD            ((reg32 *) Command_RX__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Command_RX interrupt. */
#define Command_RX_INTC_CLR_PD            ((reg32 *) Command_RX__INTC_CLR_PD_REG)


#endif /* CY_ISR_Command_RX_H */


/* [] END OF FILE */
