/*
 * state_machine.c
 *
 *  Created on: Nov 12, 2019
 *      Author: SURAJ THITE
 */

#include "state_machine.h"
#include "em_core.h"
#include "sleep.h"


#define sensor_init_time_ms (80)		// 80 milliseconds for the initialization of temperature sensor
#define adc_time_ms (10)				//10 milli seconds for adc
CORE_DECLARE_IRQ_STATE;

/*******************************************************************************************************
 * Function Name: state_machine(states current_state);
 * Descrtipiton : This function starts the state machine with the initialized  current state.
 * @input:current state
 * @Return : None
 *******************************************************************************************************/
void state_machine()
{
	{
		switch(current_state)
		{
		/*State 0: Wake up incase of Underflow Interrupt.
		 * 		   Enable LPM for gpio pin for i2c.
		 * 		   Delay of 80 ms.
		 */
		case i2c_powerOff_state:
			irqState=CORE_EnterCritical();
			if(event == Setup_LPM)
			{
				LOG_INFO(">>>>>>>>>>>>>ENTERED STATE ZERO<<<<<<<<<<<<<<<");
				event = null_event;		//Set Event to NULL Event
				//en_i2c();				// Enable the Low Power Energy Management of the GPIO Pin
				next_state = i2c_Wait_for_LPM_to_Complete;// switch to next state
				current_state = next_state;
				timerWaitUs(sensor_init_time_ms);	// Initialize the timer for 80 milliseconds and wait for interuppt

			}
			CORE_ExitCritical(irqState);
			break;

			/*State 1: COMP1 Underflow 80 ms event set.
			 * 		   Change the Sleep Blocking Mode
			 * 		   Write Command Function to i2c
			 */

		case i2c_Wait_for_LPM_to_Complete:
			irqState=CORE_EnterCritical();
			if(event == i2c_write_command_start)
			{
				LOG_INFO(">>>>>>>>>>>>>ENTERED STATE - 1 <<<<<<<<<<<<<<<");
				event = null_event;				//Set Event to NULL Event
				SLEEP_SleepBlockBegin(sleepEM2);//Sleep Blocking for i2c Operation in EM1 mode
				Interrupt_write_data();	// Call the i2c for sending the command to the sensor
				next_state = i2c_Wait_Write_to_Complete;
				current_state = next_state;		// switch to next state
			}
			CORE_ExitCritical(irqState);
			break;
			/*State 2: I2C IRQ Write  event set.
			 *		   Set the delay of 8 milli seconds for ADC
			 */
		case i2c_Wait_Write_to_Complete:
			irqState=CORE_EnterCritical();
			if(event == Setup_temp_timer)
			{
				LOG_INFO(">>>>>>>>>>>>>ENTERED STATE - 2 <<<<<<<<<<<<<<<");
				event = null_event;				//Set Event to NULL Event
				timerWaitUs(adc_time_ms);		//Initialize the timer for 8 milli
				next_state = i2c_Wait_for_temp_value_ADC;// switch to next state
				current_state = next_state;
			}
			CORE_ExitCritical(irqState);
			break;
			/*State 3: COMP1 8 milli seconds event SET.
			 *		   I2C_Read data from the sensor.
			 */
		case i2c_Wait_for_temp_value_ADC:
			irqState=CORE_EnterCritical();
			if(event == i2c_read_transfer_start)
			{
				LOG_INFO(">>>>>>>>>>>>>ENTERED STATE - 3 <<<<<<<<<<<<<<<");
				event = null_event;				  //Set Event to NULL Event
				Interrupt_read_data();			//Call the reading function to read the buffer values
				next_state = i2c_Wait_for_Read_to_Complete;// switch to next state
				current_state = next_state;
			}
			CORE_ExitCritical(irqState);
			break;
			/*State 4: I2C IRQ  READ  event SET.
			 *		   LOG the temperature values with time stamp.
			 *		   Disable the LPM
			 *		   Sleep block end to EM2
			 */
		case i2c_Wait_for_Read_to_Complete:
			irqState=CORE_EnterCritical();
			if(event == Temperature_Calc)
			{
				LOG_INFO(">>>>>>>>>>>>>ENTERED STATE - 4 <<<<<<<<<<<<<<<");
				event = null_event;				  //Set Event to NULL Event
				{
					temp_data_print();				//Print the Temperature Data
					Temperature_calculation_for_BLE(); //Temperature calculation for BLE
				}
				SLEEP_SleepBlockEnd(sleepEM2);	// End Blocking on Sleep
				next_state = i2c_powerOff_state;// switch to next state
				current_state = next_state;

			}
			CORE_ExitCritical(irqState);
			break;
		}
	}
}
