/*******************************************************************************
* File Name: Servo_Out2A.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Servo_Out2A_H) /* Pins Servo_Out2A_H */
#define CY_PINS_Servo_Out2A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Servo_Out2A_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Servo_Out2A__PORT == 15 && ((Servo_Out2A__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Servo_Out2A_Write(uint8 value) ;
void    Servo_Out2A_SetDriveMode(uint8 mode) ;
uint8   Servo_Out2A_ReadDataReg(void) ;
uint8   Servo_Out2A_Read(void) ;
uint8   Servo_Out2A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Servo_Out2A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Servo_Out2A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Servo_Out2A_DM_RES_UP          PIN_DM_RES_UP
#define Servo_Out2A_DM_RES_DWN         PIN_DM_RES_DWN
#define Servo_Out2A_DM_OD_LO           PIN_DM_OD_LO
#define Servo_Out2A_DM_OD_HI           PIN_DM_OD_HI
#define Servo_Out2A_DM_STRONG          PIN_DM_STRONG
#define Servo_Out2A_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Servo_Out2A_MASK               Servo_Out2A__MASK
#define Servo_Out2A_SHIFT              Servo_Out2A__SHIFT
#define Servo_Out2A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Servo_Out2A_PS                     (* (reg8 *) Servo_Out2A__PS)
/* Data Register */
#define Servo_Out2A_DR                     (* (reg8 *) Servo_Out2A__DR)
/* Port Number */
#define Servo_Out2A_PRT_NUM                (* (reg8 *) Servo_Out2A__PRT) 
/* Connect to Analog Globals */                                                  
#define Servo_Out2A_AG                     (* (reg8 *) Servo_Out2A__AG)                       
/* Analog MUX bux enable */
#define Servo_Out2A_AMUX                   (* (reg8 *) Servo_Out2A__AMUX) 
/* Bidirectional Enable */                                                        
#define Servo_Out2A_BIE                    (* (reg8 *) Servo_Out2A__BIE)
/* Bit-mask for Aliased Register Access */
#define Servo_Out2A_BIT_MASK               (* (reg8 *) Servo_Out2A__BIT_MASK)
/* Bypass Enable */
#define Servo_Out2A_BYP                    (* (reg8 *) Servo_Out2A__BYP)
/* Port wide control signals */                                                   
#define Servo_Out2A_CTL                    (* (reg8 *) Servo_Out2A__CTL)
/* Drive Modes */
#define Servo_Out2A_DM0                    (* (reg8 *) Servo_Out2A__DM0) 
#define Servo_Out2A_DM1                    (* (reg8 *) Servo_Out2A__DM1)
#define Servo_Out2A_DM2                    (* (reg8 *) Servo_Out2A__DM2) 
/* Input Buffer Disable Override */
#define Servo_Out2A_INP_DIS                (* (reg8 *) Servo_Out2A__INP_DIS)
/* LCD Common or Segment Drive */
#define Servo_Out2A_LCD_COM_SEG            (* (reg8 *) Servo_Out2A__LCD_COM_SEG)
/* Enable Segment LCD */
#define Servo_Out2A_LCD_EN                 (* (reg8 *) Servo_Out2A__LCD_EN)
/* Slew Rate Control */
#define Servo_Out2A_SLW                    (* (reg8 *) Servo_Out2A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Servo_Out2A_PRTDSI__CAPS_SEL       (* (reg8 *) Servo_Out2A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Servo_Out2A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Servo_Out2A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Servo_Out2A_PRTDSI__OE_SEL0        (* (reg8 *) Servo_Out2A__PRTDSI__OE_SEL0) 
#define Servo_Out2A_PRTDSI__OE_SEL1        (* (reg8 *) Servo_Out2A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Servo_Out2A_PRTDSI__OUT_SEL0       (* (reg8 *) Servo_Out2A__PRTDSI__OUT_SEL0) 
#define Servo_Out2A_PRTDSI__OUT_SEL1       (* (reg8 *) Servo_Out2A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Servo_Out2A_PRTDSI__SYNC_OUT       (* (reg8 *) Servo_Out2A__PRTDSI__SYNC_OUT) 


#if defined(Servo_Out2A__INTSTAT)  /* Interrupt Registers */

    #define Servo_Out2A_INTSTAT                (* (reg8 *) Servo_Out2A__INTSTAT)
    #define Servo_Out2A_SNAP                   (* (reg8 *) Servo_Out2A__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Servo_Out2A_H */


/* [] END OF FILE */
