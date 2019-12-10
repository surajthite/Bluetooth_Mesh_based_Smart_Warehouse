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
	null_state,
	configured,
	getreading,
	Completed,

}states;


typedef enum
{
	null_event,
	takereading,
	transfer_complete,
	transfer_error,

}events;

//create the instances of enum for monitoring current_state, Previous_state.
states current_state, next_state , Prev_State;
events event;

#define SENSOR_ADDR 0X5A
#define HW_ID 0X20
#define ALG_RES 0X02
#define STATUS_REG 0X00
#define MEAS_MODE 0X01
#define APP_START 0xF4
//#define ERROR_ID 0XE0

/*Defines for bits of status register*/
#define APP_VALID 1<<4
#define DATA_READY 1<<3
#define FW_MODE 1<<7
#endif /* SRC_STATE_MACHINE_H_ */
