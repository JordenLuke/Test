/*******************************************************************************
* File Name: Servo_B_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Servo_B.h"

static Servo_B_backupStruct Servo_B_backup;


/*******************************************************************************
* Function Name: Servo_B_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_B_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Servo_B_SaveConfig(void) 
{

    #if(!Servo_B_UsingFixedFunction)
        #if(!Servo_B_PWMModeIsCenterAligned)
            Servo_B_backup.PWMPeriod = Servo_B_ReadPeriod();
        #endif /* (!Servo_B_PWMModeIsCenterAligned) */
        Servo_B_backup.PWMUdb = Servo_B_ReadCounter();
        #if (Servo_B_UseStatus)
            Servo_B_backup.InterruptMaskValue = Servo_B_STATUS_MASK;
        #endif /* (Servo_B_UseStatus) */

        #if(Servo_B_DeadBandMode == Servo_B__B_PWM__DBM_256_CLOCKS || \
            Servo_B_DeadBandMode == Servo_B__B_PWM__DBM_2_4_CLOCKS)
            Servo_B_backup.PWMdeadBandValue = Servo_B_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Servo_B_KillModeMinTime)
             Servo_B_backup.PWMKillCounterPeriod = Servo_B_ReadKillTime();
        #endif /* (Servo_B_KillModeMinTime) */

        #if(Servo_B_UseControl)
            Servo_B_backup.PWMControlRegister = Servo_B_ReadControlRegister();
        #endif /* (Servo_B_UseControl) */
    #endif  /* (!Servo_B_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_B_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_B_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_B_RestoreConfig(void) 
{
        #if(!Servo_B_UsingFixedFunction)
            #if(!Servo_B_PWMModeIsCenterAligned)
                Servo_B_WritePeriod(Servo_B_backup.PWMPeriod);
            #endif /* (!Servo_B_PWMModeIsCenterAligned) */

            Servo_B_WriteCounter(Servo_B_backup.PWMUdb);

            #if (Servo_B_UseStatus)
                Servo_B_STATUS_MASK = Servo_B_backup.InterruptMaskValue;
            #endif /* (Servo_B_UseStatus) */

            #if(Servo_B_DeadBandMode == Servo_B__B_PWM__DBM_256_CLOCKS || \
                Servo_B_DeadBandMode == Servo_B__B_PWM__DBM_2_4_CLOCKS)
                Servo_B_WriteDeadTime(Servo_B_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Servo_B_KillModeMinTime)
                Servo_B_WriteKillTime(Servo_B_backup.PWMKillCounterPeriod);
            #endif /* (Servo_B_KillModeMinTime) */

            #if(Servo_B_UseControl)
                Servo_B_WriteControlRegister(Servo_B_backup.PWMControlRegister);
            #endif /* (Servo_B_UseControl) */
        #endif  /* (!Servo_B_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Servo_B_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_B_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Servo_B_Sleep(void) 
{
    #if(Servo_B_UseControl)
        if(Servo_B_CTRL_ENABLE == (Servo_B_CONTROL & Servo_B_CTRL_ENABLE))
        {
            /*Component is enabled */
            Servo_B_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Servo_B_backup.PWMEnableState = 0u;
        }
    #endif /* (Servo_B_UseControl) */

    /* Stop component */
    Servo_B_Stop();

    /* Save registers configuration */
    Servo_B_SaveConfig();
}


/*******************************************************************************
* Function Name: Servo_B_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_B_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_B_Wakeup(void) 
{
     /* Restore registers values */
    Servo_B_RestoreConfig();

    if(Servo_B_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Servo_B_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
