/*******************************************************************************
* File Name: Servo_A_PM.c
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

#include "Servo_A.h"

static Servo_A_backupStruct Servo_A_backup;


/*******************************************************************************
* Function Name: Servo_A_SaveConfig
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
*  Servo_A_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Servo_A_SaveConfig(void) 
{

    #if(!Servo_A_UsingFixedFunction)
        #if(!Servo_A_PWMModeIsCenterAligned)
            Servo_A_backup.PWMPeriod = Servo_A_ReadPeriod();
        #endif /* (!Servo_A_PWMModeIsCenterAligned) */
        Servo_A_backup.PWMUdb = Servo_A_ReadCounter();
        #if (Servo_A_UseStatus)
            Servo_A_backup.InterruptMaskValue = Servo_A_STATUS_MASK;
        #endif /* (Servo_A_UseStatus) */

        #if(Servo_A_DeadBandMode == Servo_A__B_PWM__DBM_256_CLOCKS || \
            Servo_A_DeadBandMode == Servo_A__B_PWM__DBM_2_4_CLOCKS)
            Servo_A_backup.PWMdeadBandValue = Servo_A_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Servo_A_KillModeMinTime)
             Servo_A_backup.PWMKillCounterPeriod = Servo_A_ReadKillTime();
        #endif /* (Servo_A_KillModeMinTime) */

        #if(Servo_A_UseControl)
            Servo_A_backup.PWMControlRegister = Servo_A_ReadControlRegister();
        #endif /* (Servo_A_UseControl) */
    #endif  /* (!Servo_A_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_A_RestoreConfig
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
*  Servo_A_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_A_RestoreConfig(void) 
{
        #if(!Servo_A_UsingFixedFunction)
            #if(!Servo_A_PWMModeIsCenterAligned)
                Servo_A_WritePeriod(Servo_A_backup.PWMPeriod);
            #endif /* (!Servo_A_PWMModeIsCenterAligned) */

            Servo_A_WriteCounter(Servo_A_backup.PWMUdb);

            #if (Servo_A_UseStatus)
                Servo_A_STATUS_MASK = Servo_A_backup.InterruptMaskValue;
            #endif /* (Servo_A_UseStatus) */

            #if(Servo_A_DeadBandMode == Servo_A__B_PWM__DBM_256_CLOCKS || \
                Servo_A_DeadBandMode == Servo_A__B_PWM__DBM_2_4_CLOCKS)
                Servo_A_WriteDeadTime(Servo_A_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Servo_A_KillModeMinTime)
                Servo_A_WriteKillTime(Servo_A_backup.PWMKillCounterPeriod);
            #endif /* (Servo_A_KillModeMinTime) */

            #if(Servo_A_UseControl)
                Servo_A_WriteControlRegister(Servo_A_backup.PWMControlRegister);
            #endif /* (Servo_A_UseControl) */
        #endif  /* (!Servo_A_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Servo_A_Sleep
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
*  Servo_A_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Servo_A_Sleep(void) 
{
    #if(Servo_A_UseControl)
        if(Servo_A_CTRL_ENABLE == (Servo_A_CONTROL & Servo_A_CTRL_ENABLE))
        {
            /*Component is enabled */
            Servo_A_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Servo_A_backup.PWMEnableState = 0u;
        }
    #endif /* (Servo_A_UseControl) */

    /* Stop component */
    Servo_A_Stop();

    /* Save registers configuration */
    Servo_A_SaveConfig();
}


/*******************************************************************************
* Function Name: Servo_A_Wakeup
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
*  Servo_A_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_A_Wakeup(void) 
{
     /* Restore registers values */
    Servo_A_RestoreConfig();

    if(Servo_A_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Servo_A_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
