
/*
 * 	Letimer0.c
 *
 *  Created on: Sep 25, 2019
 *      Author: SURAJ THITE
 */

#include "em_letimer.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_core.h"
#include "letimer0.h"
#include "log.h"
uint32_t rollover_count =0;

uint16_t COMP1_value;
uint16_t  max_COMP0_count;
uint32_t current_value;

/*******************************************************************************************************
 * Function Name: LETIMER_CONFIG_START()
 * Description:
 * This function configures LETIMER0 in EM3 Mode.
 * @Input:None
 * @Return Type : None
 *******************************************************************************************************/
void LETIMER_CONFIG_START()
{
#if(EM==0|EM==1|EM==2)

	CMU_OscillatorEnable(cmuOsc_LFXO,true,true); //Enable the LFXO
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);// Clock source is LFXO
	//Set Prescaler to 4 inorder to put the Frequency value in range
	/* F_OSCILLATOR / PRESCALER  x No of Ticks for 16 bit timer (2^16-1) Hence  Setting Prescaler of 16 i.e. 2^4 makes the frequency in the given time range*/
	CMU_ClockDivSet(cmuClock_LETIMER0, 4);

#define LETIMER_COMP0_VAL LED_Total_Time_Period_ms*8.192  //Define value to be loaded in the COMP0 register for the total time of the waveform. Value to be loaded= Total in milliSeconds* Frequency of Clock /1000
	//#define LETIMER_COMP1_VAL LED_On_Time_ms*8.192 //Define value to be loaded in COMP on register for Change of state from Off state to On state. Value to be loaded = ON time in milliseconds* Frequency of Clock / 100


#endif

	/* Define Same configuration for EM3 Mode with Oscillator set to ULFRCO with frequency of 1000Hz*/
#if(EM==3)

	CMU_OscillatorEnable(cmuOsc_ULFRCO,true,true); //Enable Ultra Low Frequency Oscillator
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);// Clock source is ULFRCO
#define LETIMER_COMP0_VAL LED_Total_Time_Period_ms*1 //Load value into COMP0 Register for total time period
#define LETIMER_COMP1_VAL LED_On_Time_ms*1 // Load Value into Comp1 Register for on time period

#endif
	CMU_ClockEnable(cmuClock_LFA, true); // Enable LFA Parent Clock
	CMU_ClockEnable(cmuClock_LETIMER0, true); //Enable Clock to LETIMER0 Peripheral
	/* Set configurations for LETIMER 0 */

	const LETIMER_Init_TypeDef LETIMER_INITIAL_CONFIG = {
			.enable = true,               /* Start counting when init completed. */
			.debugRun = true,            /* Counter shall not keep running during debug halt. */
			.comp0Top = true,
			.repMode = letimerRepeatFree/* Load COMP0 register into CNT when counter underflows. COMP0 is used as TOP */
	};


	LETIMER_CompareSet(LETIMER0, 0,LETIMER_COMP0_VAL);     // Load the Calculated COMP0 Value into COMP0 Resister Depending Upon Energy Mode
	LETIMER_Init(LETIMER0, &LETIMER_INITIAL_CONFIG); // Initialize the LETIMER BY PASSING LETIMER_INITIAL_CONFIG FOR LETIMER0
	NVIC_EnableIRQ( LETIMER0_IRQn );//Enable Nested Interrupts
	LETIMER_IntEnable( LETIMER0, LETIMER_IFS_COMP1|LETIMER_IFS_UF); //Enable LETIMER0 Interrupt for Underflow and COMP1 flags
	LETIMER_Enable(LETIMER0,true); // Enable the LETIMER0 in Run Mode.
}
// The Configuration of the LETIMER and its IRQ handling along with Energy modes have been referenced by : https://www.silabs.com/support/resources.ct-example-code

/*******************************************************************************************************
 * Function Name: delay_us(uint32_t us)
 * Description :
 * This function configures delays provided by the user in milliseconds.
 * The Roll - Over Condition of the timer is taken care of in this code.
 * COMP1 Interrupt is Enabled in this version of the code.
 *  @Input:Time for Delay in Milli Seconds
 *  @Return Type: None
 *******************************************************************************************************/
void timerWaitUs(uint32_t ms)
{
	current_value = LETIMER_CounterGet(LETIMER0);
	if (current_value>=ms)
	{
		COMP1_value =  current_value - ms;
	}
	else
	{
		max_COMP0_count=LETIMER_CompareGet(LETIMER0,0);
		COMP1_value = (max_COMP0_count-ms+current_value);
	}
	LETIMER_CompareSet(LETIMER0, 1,COMP1_value);	// Set the timer to COMP1 Register.
	LETIMER_IntEnable(LETIMER0, LETIMER_IEN_COMP1);	// Set the Interrupt for COMP1 Register.
}
/*******************************************************************************************************
 * Function Name: LETIMER0_IRQ Handler.
 * Description::
 *This is an interrupt handler for LETIMER0.
 *This Upon Underflow, the state is changed to PowerOff state and event is set to SET UP LPM for
 *i2c to work.The COMP1 interrupt handles the delay of 80 ms and 10 milliseconds implementing logical
 *conditional execution depending upon the previous state.
 *The Roll Over is incremented upon underflow interrupt and passed for time stamping.
 *@Input: None
 *@Return: None
 *******************************************************************************************************/
void LETIMER0_IRQHandler(void)  // IRQ Handler
{
	//LOG_INFO("COMP1 Interrupt");
	CORE_ATOMIC_IRQ_DISABLE();
	uint32_t interrupt = LETIMER_IntGet( LETIMER0 ); // Storing inturrupt register value of LETIMER in temp variable store_int
	LETIMER_IntClear( LETIMER0, interrupt );  // clear LETIMER inturrupt.

	if( interrupt & LETIMER_IFS_COMP1)  // Condition check for COM1
	{
		LETIMER_CompareSet(LETIMER0, 1, 0xFFFF);
		LETIMER_IntDisable(LETIMER0,LETIMER_IFC_COMP1);
	}

	if( interrupt & LETIMER_IFS_UF)   // Condition check for Under_flow
		{
			rollover_count = rollover_count+1 ; // Update the roll over count for the LOG Info
		}
	CORE_ATOMIC_IRQ_ENABLE();
}


