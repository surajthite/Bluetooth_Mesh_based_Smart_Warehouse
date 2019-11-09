/*
 * HEADER FILE FOR LOW ENERGY TIMER 0
 * letimero.h
 *
 *  Created on: Sep 10, 2019
 *  Author: SURAJ THITE
 */

#ifndef SRC_LETIMERO_H_
#define SRC_LETIMERO_H_
#define EM (3)       //Define the Energy Mode Of Operation
#define  LED_On_Time_ms  (1500)   //Define the LED_On_Time in seconds
#define  LED_Total_Time_Period_ms (3000) //Define the LED total time period in seconds
#include "bg_types.h"

void LETIMER0_setup(void); // Function to Initialize the LETIMER0 and RUN it
void Enable_Interrupt_Start_Timer(); // Function for Enabling Interrupts for LETIMER0
void timerWaitUs(uint32_t ms);
void LETIMER_CONFIG_START();
#define UF_FLAG 0x01
#endif /* SRC_LETIMERO_H_ */
