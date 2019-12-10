/*
 * state_machine.c
 *
 *  Created on: Nov 12, 2019
 *      Author: SURAJ THITE
 */

#include "state_machine.h"
#include "em_core.h"
#include "sleep.h"
#include "log.h"
#include "i2c_interrupt.h"
#include "gecko_main.h"

extern uint8_t aqi_data_buffer[2];	//Buffer to store AQI_data
#define AQI_KEY (0X4000)	//Key to store Air Quality Index Persistant data

uint32_t configured_flag=0;	//COnfigured Flag
uint16_t aqi_max=0;	//Maximum Air Quality Index value to be stored in the persistant data.

/*******************************************************************************************************
 * Function Name: state_machine_1(void);
 * Descrtipiton : This function is an interrupt based state machine for Low power functionality reducing current
 *  by 2 milli amps compared to polling
 * @input:void
 * @Return : void
 *******************************************************************************************************/

void state_machine_1()
{
	switch(Prev_State)
	{
	CORE_irqState_t irqState;
	case configured:

		if(event == takereading)
		{
			irqState=CORE_EnterCritical();	//Enter critical Region
			LOG_INFO(" Take Reading Event Recieved");
			event = null_event;		//Clear Events
#if LPM_ENABLE
			GPIO_PinOutClear(WAKE_PIN_PORT,WAKE_PIN); //Turning on the sensor
#endif
			Interrupt_write_read();	//Configure I2C in read write mode and send command to the sensor
			current_state = getreading;	//Change to next state
		}
		else
		{
			event = null_event;	//Clear Event
			current_state = configured;	//Set next state to configured state
			NVIC_DisableIRQ(I2C0_IRQn);	//Disable Interrupts  for I2C0
		}
		CORE_ExitCritical(irqState);	//Exit Critical Region
		break;

	case getreading:

		irqState=CORE_EnterCritical();	//Enter Critical Region
		if(event == transfer_complete)	//Check for Transfer Complete Event
		{
			LOG_INFO(" GET READING ");
			LOG_INFO(" Get Reading Event Recieved");
			event = null_event;
			uint16_t aqi_data=0;
			LOG_INFO("value in data buffer AQI[0] is %d",aqi_data_buffer[0]);
			LOG_INFO("value in data buffer AQI[1] is %d",aqi_data_buffer[1]);
//Calculate the 16 bit ppm values from i2c buffer
			aqi_data= aqi_data_buffer[0];
			aqi_data <<= 8;
			aqi_data |= aqi_data_buffer[1];
//Display ppm value on the console
			LOG_INFO("Current ppm  value is %d",aqi_data);
//Update it on the LCD screen
			displayPrintf(DISPLAY_ROW_PPM,"CO2:%d ppm",aqi_data);
//Store the maximum AQI data in the persistant memory
			if(aqi_data > aqi_max)	//Store Peristant Dataa if value Exceeds maximum value
			{
				StorePersistentData(AQI_KEY,aqi_data);
				aqi_max = aqi_data;
			}
#if LPM_ENABLE
	GPIO_PinOutSet(WAKE_PIN_PORT,WAKE_PIN);
#endif

		send_ppm_friend(aqi_data);//Send ppm data to friend

			current_state = configured;	//Change current state to configured
		}
		else if(event == transfer_error)
		{
			event = null_event;	//Clear event
			current_state = configured;	//Change current state to configured
			NVIC_DisableIRQ(I2C0_IRQn);	//Disable interrupts for I2C0
		}
		CORE_ExitCritical(irqState);//Exit ciritical Region
		break;

	default:
		LOG_INFO("ERROR STATE");
		break;
	}
	if(Prev_State != current_state)
	{
		LOG_INFO("State Machine Changing State from: %d to %d ", Prev_State, current_state);	//Print the state transiton
		Prev_State=current_state;
	}
}

/*******************************************************************************************************
 * Function Name: void CCS811_config()
 * Descrtipiton : This function does initial configuration of the sensor by writing APP_START command
 * and checking for valid firmware mode.
 * @input:void
 * @Return : void
 *******************************************************************************************************/


void CCS811_config()
{
	I2C_TransferSeq_TypeDef init;
	uint16_t getval;

	init.addr= SENSOR_ADDR << 1;	//Configure the slave address
	uint8_t command = STATUS_REG;
	init.buf[0].data= &command;

	Interrupt_write_data(init,1);	//Send the STATUS_REG command to the sensor

	timerWaitUs(10);	//wait for read

	getval=Interrupt_read_data(init,1);	//Read data from the I2c Buffer

	LOG_INFO("The Value of Status Register is  %x\n",getval);	//Display status register value

	if(getval & APP_VALID)	//Check for valid applicaiton firmware presence
	{
		LOG_INFO("Valid Firmware Found! Writing APP_START to Sensor \n");
	}

	command=APP_START;
	init.buf[0].data=&command;

	Interrupt_write_data(init,1);	//Send application start command the sensor
	timerWaitUs(10);	//wait for 10 milli seconds

	LOG_INFO("Checking Status Register Again \n");

	command=STATUS_REG;
	init.buf[0].data=&command;

	Interrupt_write_data(init,1);	//Send command to read status register value
	timerWaitUs(10);	//wait for 10 milli seconds

	getval=Interrupt_read_data(init,1);	//Read status register value
	LOG_INFO("The value of Status  Register is %x\n",getval);	//Print the status register value

	if(getval & FW_MODE)
	{
		LOG_INFO("Mode changed to firmware mode\n"); //Check for mode change to firmware mode
	}
}

/*******************************************************************************************************
 * Function Name: void CCS81_change_mode()
 * Descrtipiton : This function initialize the senosor to MEAS mode to send CO2 ppm values
 * @input:void
 * @Return : void
 *******************************************************************************************************/
void CCS81_change_mode()
{
	//Writing to MEAS_MODE register the mode in which the sensor will operate. Mode 1
	I2C_TransferSeq_TypeDef init;
	uint16_t getval;

	init.addr= SENSOR_ADDR << 1;
	uint8_t command[2]={ 0x01, 0x18}; // Setting the address to Measure mode register  (0x01) and writing 0x18 to it.
	init.buf[0].data=command;
	Interrupt_write_data(init,2);
	timerWaitUs(10);

	command[0]=MEAS_MODE;
	init.buf[0].data=command;
	Interrupt_write_data(init,1);	//Configure sensor to MEAS mode
	timerWaitUs(10);	//Wait for 10 milli seconds

	getval=Interrupt_read_data(init,1);	//Read register value and print on the console
	LOG_INFO("Measured  Register value  is %x\n",getval);

}
/*******************************************************************************************************
 * Function Name: uint16_t get_ppm()
 * Descrtipiton : This function returns the ppm value from the sensor through i2c polling implementing Low
 * Power Functionality
 * @input:void
 * @Return : uint16_t co2 ppm value
 *******************************************************************************************************/

uint16_t get_ppm()
{
#if LPM_ENABLE
	GPIO_PinOutClear(WAKE_PIN_PORT,WAKE_PIN); //Turning on the sensor
#endif
	I2C_TransferSeq_TypeDef init;
	uint16_t getval;
	init.addr= SENSOR_ADDR << 1;	//Set the slave address
	uint16_t command=STATUS_REG;
	init.buf[0].data=&command;	//Send write command for STATUS register

	Interrupt_write_data(init,1);	//Start write
	timerWaitUs(10);	//Wait for 10 milli seconds

	getval=Interrupt_read_data(init,1);	// Read status register value
	if(getval & DATA_READY)	//If 3rd bit is set then red the ALG_register value
	{
		init.addr= SENSOR_ADDR << 1;
		uint16_t command=ALG_RES;
		init.buf[0].data=&command;	//Send command to read ALG_register value

		Interrupt_write_data(init,1);	//Initiate write transfer
		timerWaitUs(10);	//Wait for 10 milli seconds
		getval =0;
		getval=Interrupt_read_data(init,2);	//Read PPM value and store it in a variable
		LOG_INFO("Current ppm value is %d\n",getval);	//Print the ppm value on the console
#if LPM_ENABLE
		GPIO_PinOutSet(WAKE_PIN_PORT,WAKE_PIN);	//Turning off the sensor.
#endif
	}
	return getval; 	//Return the ppm value to the calling function
}
