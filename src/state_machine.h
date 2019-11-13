/*
 * state_machine.h
 *
 *  Created on: Nov 12, 2019
 *      Author: SURAJ THITE
 */

#ifndef SRC_STATE_MACHINE_H_
#define SRC_STATE_MACHINE_H_


typedef enum
{
	i2c_powerOff_state,
	i2c_Wait_for_LPM_to_Complete,
	i2c_Wait_Write_to_Complete,
	i2c_Wait_for_temp_value_ADC,
	i2c_Wait_for_Read_to_Complete,
}states;
typedef enum
{
	null_event,
	Setup_LPM,
	i2c_write_command_start,
	Setup_temp_timer,
	i2c_read_transfer_start,
	Temperature_Calc
}events;

//create the instances of enum for monitoring current_state, Previous_state.
states current_state, next_state;
events event;
#endif /* SRC_STATE_MACHINE_H_ */
