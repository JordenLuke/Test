/*******************************************************************************
* File Name: Servo_B.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Servo_B.h"

/* Error message for removed <resource> through optimization */
#ifdef Servo_B_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* Servo_B_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 Servo_B_initVar = 0u;


/*******************************************************************************
* Function Name: Servo_B_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_B_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Servo_B_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Servo_B_initVar == 0u)
    {
        Servo_B_Init();
        Servo_B_initVar = 1u;
    }
    Servo_B_Enable();

}


/*******************************************************************************
* Function Name: Servo_B_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Servo_B_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Servo_B_Init(void) 
{
    #if (Servo_B_UsingFixedFunction || Servo_B_UseControl)
        uint8 ctrl;
    #endif /* (Servo_B_UsingFixedFunction || Servo_B_UseControl) */

    #if(!Servo_B_UsingFixedFunction)
        #if(Servo_B_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 Servo_B_interruptState;
        #endif /* (Servo_B_UseStatus) */
    #endif /* (!Servo_B_UsingFixedFunction) */

    #if (Servo_B_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        Servo_B_CONTROL |= Servo_B_CFG0_MODE;
        #if (Servo_B_DeadBand2_4)
            Servo_B_CONTROL |= Servo_B_CFG0_DB;
        #endif /* (Servo_B_DeadBand2_4) */

        ctrl = Servo_B_CONTROL3 & ((uint8 )(~Servo_B_CTRL_CMPMODE1_MASK));
        Servo_B_CONTROL3 = ctrl | Servo_B_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Servo_B_RT1 &= ((uint8)(~Servo_B_RT1_MASK));
        Servo_B_RT1 |= Servo_B_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        Servo_B_RT1 &= ((uint8)(~Servo_B_SYNCDSI_MASK));
        Servo_B_RT1 |= Servo_B_SYNCDSI_EN;

    #elif (Servo_B_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = Servo_B_CONTROL & ((uint8)(~Servo_B_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~Servo_B_CTRL_CMPMODE1_MASK));
        Servo_B_CONTROL = ctrl | Servo_B_DEFAULT_COMPARE2_MODE |
                                   Servo_B_DEFAULT_COMPARE1_MODE;
    #endif /* (Servo_B_UsingFixedFunction) */

    #if (!Servo_B_UsingFixedFunction)
        #if (Servo_B_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            Servo_B_AUX_CONTROLDP0 |= (Servo_B_AUX_CTRL_FIFO0_CLR);
        #else /* (Servo_B_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            Servo_B_AUX_CONTROLDP0 |= (Servo_B_AUX_CTRL_FIFO0_CLR);
            Servo_B_AUX_CONTROLDP1 |= (Servo_B_AUX_CTRL_FIFO0_CLR);
        #endif /* (Servo_B_Resolution == 8) */

        Servo_B_WriteCounter(Servo_B_INIT_PERIOD_VALUE);
    #endif /* (!Servo_B_UsingFixedFunction) */

    Servo_B_WritePeriod(Servo_B_INIT_PERIOD_VALUE);

        #if (Servo_B_UseOneCompareMode)
            Servo_B_WriteCompare(Servo_B_INIT_COMPARE_VALUE1);
        #else
            Servo_B_WriteCompare1(Servo_B_INIT_COMPARE_VALUE1);
            Servo_B_WriteCompare2(Servo_B_INIT_COMPARE_VALUE2);
        #endif /* (Servo_B_UseOneCompareMode) */

        #if (Servo_B_KillModeMinTime)
            Servo_B_WriteKillTime(Servo_B_MinimumKillTime);
        #endif /* (Servo_B_KillModeMinTime) */

        #if (Servo_B_DeadBandUsed)
            Servo_B_WriteDeadTime(Servo_B_INIT_DEAD_TIME);
        #endif /* (Servo_B_DeadBandUsed) */

    #if (Servo_B_UseStatus || Servo_B_UsingFixedFunction)
        Servo_B_SetInterruptMode(Servo_B_INIT_INTERRUPTS_MODE);
    #endif /* (Servo_B_UseStatus || Servo_B_UsingFixedFunction) */

    #if (Servo_B_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        Servo_B_GLOBAL_ENABLE |= Servo_B_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        Servo_B_CONTROL2 |= Servo_B_CTRL2_IRQ_SEL;
    #else
        #if(Servo_B_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Servo_B_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Servo_B_STATUS_AUX_CTRL |= Servo_B_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(Servo_B_interruptState);

            /* Clear the FIFO to enable the Servo_B_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            Servo_B_ClearFIFO();
        #endif /* (Servo_B_UseStatus) */
    #endif /* (Servo_B_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_B_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void Servo_B_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Servo_B_UsingFixedFunction)
        Servo_B_GLOBAL_ENABLE |= Servo_B_BLOCK_EN_MASK;
        Servo_B_GLOBAL_STBY_ENABLE |= Servo_B_BLOCK_STBY_EN_MASK;
    #endif /* (Servo_B_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (Servo_B_UseControl || Servo_B_UsingFixedFunction)
        Servo_B_CONTROL |= Servo_B_CTRL_ENABLE;
    #endif /* (Servo_B_UseControl || Servo_B_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_B_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void Servo_B_Stop(void) 
{
    #if (Servo_B_UseControl || Servo_B_UsingFixedFunction)
        Servo_B_CONTROL &= ((uint8)(~Servo_B_CTRL_ENABLE));
    #endif /* (Servo_B_UseControl || Servo_B_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (Servo_B_UsingFixedFunction)
        Servo_B_GLOBAL_ENABLE &= ((uint8)(~Servo_B_BLOCK_EN_MASK));
        Servo_B_GLOBAL_STBY_ENABLE &= ((uint8)(~Servo_B_BLOCK_STBY_EN_MASK));
    #endif /* (Servo_B_UsingFixedFunction) */
}

#if (Servo_B_UseOneCompareMode)
    #if (Servo_B_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Servo_B_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Servo_B_SetCompareMode(uint8 comparemode) 
        {
            #if(Servo_B_UsingFixedFunction)

                #if(0 != Servo_B_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << Servo_B_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != Servo_B_CTRL_CMPMODE1_SHIFT) */

                Servo_B_CONTROL3 &= ((uint8)(~Servo_B_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                Servo_B_CONTROL3 |= comparemodemasked;

            #elif (Servo_B_UseControl)

                #if(0 != Servo_B_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << Servo_B_CTRL_CMPMODE1_SHIFT)) &
                                                Servo_B_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & Servo_B_CTRL_CMPMODE1_MASK;
                #endif /* (0 != Servo_B_CTRL_CMPMODE1_SHIFT) */

                #if(0 != Servo_B_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << Servo_B_CTRL_CMPMODE2_SHIFT)) &
                                               Servo_B_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & Servo_B_CTRL_CMPMODE2_MASK;
                #endif /* (0 != Servo_B_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                Servo_B_CONTROL &= ((uint8)(~(Servo_B_CTRL_CMPMODE1_MASK |
                                            Servo_B_CTRL_CMPMODE2_MASK)));
                Servo_B_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (Servo_B_UsingFixedFunction) */
        }
    #endif /* Servo_B_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (Servo_B_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Servo_B_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Servo_B_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != Servo_B_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << Servo_B_CTRL_CMPMODE1_SHIFT)) &
                                           Servo_B_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & Servo_B_CTRL_CMPMODE1_MASK;
            #endif /* (0 != Servo_B_CTRL_CMPMODE1_SHIFT) */

            #if (Servo_B_UseControl)
                Servo_B_CONTROL &= ((uint8)(~Servo_B_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                Servo_B_CONTROL |= comparemodemasked;
            #endif /* (Servo_B_UseControl) */
        }
    #endif /* Servo_B_CompareMode1SW */

#if (Servo_B_CompareMode2SW)


    /*******************************************************************************
    * Function Name: Servo_B_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Servo_B_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != Servo_B_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << Servo_B_CTRL_CMPMODE2_SHIFT)) &
                                                 Servo_B_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & Servo_B_CTRL_CMPMODE2_MASK;
        #endif /* (0 != Servo_B_CTRL_CMPMODE2_SHIFT) */

        #if (Servo_B_UseControl)
            Servo_B_CONTROL &= ((uint8)(~Servo_B_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            Servo_B_CONTROL |= comparemodemasked;
        #endif /* (Servo_B_UseControl) */
    }
    #endif /*Servo_B_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!Servo_B_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Servo_B_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void Servo_B_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(Servo_B_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: Servo_B_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 Servo_B_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(Servo_B_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(Servo_B_CAPTURE_LSB_PTR));
    }

    #if (Servo_B_UseStatus)


        /*******************************************************************************
        * Function Name: Servo_B_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Servo_B_ClearFIFO(void) 
        {
            while(0u != (Servo_B_ReadStatusRegister() & Servo_B_STATUS_FIFONEMPTY))
            {
                (void)Servo_B_ReadCapture();
            }
        }

    #endif /* Servo_B_UseStatus */

#endif /* !Servo_B_UsingFixedFunction */


/*******************************************************************************
* Function Name: Servo_B_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void Servo_B_WritePeriod(uint16 period) 
{
    #if(Servo_B_UsingFixedFunction)
        CY_SET_REG16(Servo_B_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(Servo_B_PERIOD_LSB_PTR, period);
    #endif /* (Servo_B_UsingFixedFunction) */
}

#if (Servo_B_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Servo_B_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void Servo_B_WriteCompare(uint16 compare) \
                                       
    {
        #if(Servo_B_UsingFixedFunction)
            CY_SET_REG16(Servo_B_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Servo_B_COMPARE1_LSB_PTR, compare);
        #endif /* (Servo_B_UsingFixedFunction) */

        #if (Servo_B_PWMMode == Servo_B__B_PWM__DITHER)
            #if(Servo_B_UsingFixedFunction)
                CY_SET_REG16(Servo_B_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(Servo_B_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (Servo_B_UsingFixedFunction) */
        #endif /* (Servo_B_PWMMode == Servo_B__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: Servo_B_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Servo_B_WriteCompare1(uint16 compare) \
                                        
    {
        #if(Servo_B_UsingFixedFunction)
            CY_SET_REG16(Servo_B_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Servo_B_COMPARE1_LSB_PTR, compare);
        #endif /* (Servo_B_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: Servo_B_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Servo_B_WriteCompare2(uint16 compare) \
                                        
    {
        #if(Servo_B_UsingFixedFunction)
            CY_SET_REG16(Servo_B_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(Servo_B_COMPARE2_LSB_PTR, compare);
        #endif /* (Servo_B_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (Servo_B_DeadBandUsed)


    /*******************************************************************************
    * Function Name: Servo_B_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Servo_B_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!Servo_B_DeadBand2_4)
            CY_SET_REG8(Servo_B_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            Servo_B_DEADBAND_COUNT &= ((uint8)(~Servo_B_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(Servo_B_DEADBAND_COUNT_SHIFT)
                Servo_B_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << Servo_B_DEADBAND_COUNT_SHIFT)) &
                                                    Servo_B_DEADBAND_COUNT_MASK;
            #else
                Servo_B_DEADBAND_COUNT |= deadtime & Servo_B_DEADBAND_COUNT_MASK;
            #endif /* (Servo_B_DEADBAND_COUNT_SHIFT) */

        #endif /* (!Servo_B_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: Servo_B_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 Servo_B_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!Servo_B_DeadBand2_4)
            return (CY_GET_REG8(Servo_B_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(Servo_B_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(Servo_B_DEADBAND_COUNT & Servo_B_DEADBAND_COUNT_MASK)) >>
                                                                           Servo_B_DEADBAND_COUNT_SHIFT));
            #else
                return (Servo_B_DEADBAND_COUNT & Servo_B_DEADBAND_COUNT_MASK);
            #endif /* (Servo_B_DEADBAND_COUNT_SHIFT) */
        #endif /* (!Servo_B_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (Servo_B_UseStatus || Servo_B_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Servo_B_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Servo_B_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(Servo_B_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: Servo_B_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 Servo_B_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(Servo_B_STATUS_PTR));
    }

#endif /* (Servo_B_UseStatus || Servo_B_UsingFixedFunction) */


#if (Servo_B_UseControl)


    /*******************************************************************************
    * Function Name: Servo_B_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 Servo_B_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(Servo_B_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: Servo_B_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Servo_B_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(Servo_B_CONTROL_PTR, control);
    }

#endif /* (Servo_B_UseControl) */


#if (!Servo_B_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Servo_B_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 Servo_B_ReadCapture(void) 
    {
        return (CY_GET_REG16(Servo_B_CAPTURE_LSB_PTR));
    }

#endif /* (!Servo_B_UsingFixedFunction) */


#if (Servo_B_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Servo_B_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 Servo_B_ReadCompare(void) 
    {
        #if(Servo_B_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(Servo_B_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(Servo_B_COMPARE1_LSB_PTR));
        #endif /* (Servo_B_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: Servo_B_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 Servo_B_ReadCompare1(void) 
    {
        return (CY_GET_REG16(Servo_B_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: Servo_B_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 Servo_B_ReadCompare2(void) 
    {
        return (CY_GET_REG16(Servo_B_COMPARE2_LSB_PTR));
    }

#endif /* (Servo_B_UseOneCompareMode) */


/*******************************************************************************
* Function Name: Servo_B_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 Servo_B_ReadPeriod(void) 
{
    #if(Servo_B_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Servo_B_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Servo_B_PERIOD_LSB_PTR));
    #endif /* (Servo_B_UsingFixedFunction) */
}

#if ( Servo_B_KillModeMinTime)


    /*******************************************************************************
    * Function Name: Servo_B_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Servo_B_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(Servo_B_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: Servo_B_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 Servo_B_ReadKillTime(void) 
    {
        return (CY_GET_REG8(Servo_B_KILLMODEMINTIME_PTR));
    }

#endif /* ( Servo_B_KillModeMinTime) */

/* [] END OF FILE */
