
/*
 * i2c_interrupt.c
 *
 *  Created on: Sep 25, 2019
 *      Author: SURAJ THITE
 */

//Header Files//
#include "i2c_interrupt.h"
#include "state_machine.h"
#include "gatt_db.h"

//Gloabl Variables//

uint8_t command_ALG_sensor = 0x02;	//Command to read AQI sensor data from I2C bus
uint8_t aqi_data_buffer[2];	//Buffer to store AQI_data
bool  write_status =0;	//Flag to store write status
bool read_status =0;	//Flag to store read status
I2C_TransferSeq_TypeDef write_config;	//Write config structure
I2C_TransferSeq_TypeDef read_config;	//Read config structure
I2C_TransferSeq_TypeDef write_read_config;	//Read config structure
float Temperature_Val  = 0;//Temporary variable for temprature calculation
uint32_t I2C_Transfer_Error_Flag =0;
uint32_t I2C_Transfer_Complete_Flag =0;
uint32_t I2C_Error =0;
uint32_t Setup_temp_timer_flag =0;


extern events event;
/*******************************************************************************************************
 * Function Name: i2c_int_init()
 * Descrtipiton : This function configures and initializes the interrupts for I2C0.
 * @input:NOne
 * @Return : None
 *******************************************************************************************************/
void i2c_int_init()
{
	I2CSPM_Init_TypeDef i2c_config_int = I2CSPM_INIT_DEFAULT;	// Set Default
	I2CSPM_Init(&i2c_config_int);
}

/*******************************************************************************************************
 * Function Name: Interrupt_write_data
 * Desciption:
 * This function configures and write the command to the buff0 and setting up the the write status register.
 * @input: None
 * @reutn :None
 *******************************************************************************************************/

void Interrupt_write_data( I2C_TransferSeq_TypeDef init, uint16_t len)
{
	I2C_TransferReturn_TypeDef ret;
	init.buf[0].len=len;	//Set the length of the comamnd to be sent
	init.flags= I2C_FLAG_WRITE;	//Set hte flags to write flag
	ret=I2CSPM_Transfer(I2C0,&init);	//Initiate polling transfer
	if(ret != i2cTransferDone)
	{
		LOG_INFO("I2C Write error");	//Log the errors
		return;
	}
}
/*******************************************************************************************************
 * Function Name: Interrupt_read_data
 * Description:
 * This function configures and reads from the buffer  while setting up the the read status register.
 * @input: None
 * @Return:None
 *******************************************************************************************************/

uint16_t Interrupt_read_data(I2C_TransferSeq_TypeDef init, uint16_t len)
{
	I2C_TransferReturn_TypeDef ret;
	uint8_t received_data[2] = {0};	//Initialize the recieve buffer
	uint16_t temp;
	init.flags= I2C_FLAG_READ;	//Set the flags to I2c Read
	init.buf[0].data= received_data;	//Set the pointer to store the value read from the sensor
	init.buf[0].len=sizeof(received_data);	//Set the length accordingly
	ret=I2CSPM_Transfer(I2C0,&init); //	//Initiate I2C SPM transfer
	if(ret != i2cTransferDone)	//Log the errors
	{
		LOG_ERROR("I2C Read error");
	}
	if(len==1)
	{
		temp = received_data[0];	//Send 8 bit value if length passed as 1
	}
	else
	{
		temp = received_data[0];
		temp <<= 8;
		temp|=(received_data[1]);	//send 16 bit value if length passed as 2
	}
	return temp;
}


/*******************************************************************************************************
 * Function Name: Interrupt_write_read
 * This function configures,writes and read mode and tx and rx data  from the buffer.
 * @input: None
 * @Return:None
 *******************************************************************************************************/


void Interrupt_write_read()
{
	write_read_config.addr =  SENSOR_ADDR << 1;	//Set the sensor address
	write_read_config.flags = I2C_FLAG_WRITE_READ;	//Initialize the flags to read write
	write_read_config.buf[0].len =	1;
	write_read_config.buf[1].len =	2;
	write_read_config.buf[0].data = &command_ALG_sensor ;	//COmmand to read CO2 value in ppm
	write_read_config.buf[1].data = aqi_data_buffer;	//Variable to store the value recieved
	NVIC_EnableIRQ(I2C0_IRQn);	//Enable interrupts
	I2C_TransferReturn_TypeDef response = I2C_TransferInit(I2C0, &write_read_config); 		/*Initialising the non polling I2c*/
	if(response != i2cTransferInProgress)	//Log the errors
	{
		LOG_INFO("Failed");
	}
	else
	{
		LOG_INFO("Transfer Done");
	}
	//I2CSPM_Transfer(I2C0,&write_read_config);

	LOG_INFO("Waiting for Interrupts");
}
/*******************************************************************************************************
 * Function Name: void Enable_I2C_Interrupts()
 * Descrtipiton : Function to enable i2c interrupts
 * @input:void
 * @Return : void
 *******************************************************************************************************/

void Enable_I2C_Interrupts()
{
	NVIC_EnableIRQ(I2C0_IRQn); // Enable NVIC Interrupts
	//I2C_IntEnable(I2C0,I2C_IEN_RXDATAV | I2C_IEN_RXFULL | I2C_IEN_TXC );// Enable Interrupts for i2C
}
/*******************************************************************************************************
 * Function Name: void Disable_I2C_Interrupts()
 * Descrtipiton : Function to disable i2c interrupts
 * @input:void
 * @Return : void
 *******************************************************************************************************/

void Disable_I2C_Interrupts()
{
	NVIC_DisableIRQ(I2C0_IRQn);
}


/*******************************************************************************************************
 * Function Name: I2C0_IRQHandler()
 * This is an interrupt handler responsible for catering the interrupt request and change the events and
 * states accordingly.
 *******************************************************************************************************/
void I2C0_IRQHandler(void)
{
	CORE_ATOMIC_IRQ_DISABLE();
	I2C_TransferReturn_TypeDef i2c_irq_status = I2C_Transfer(I2C0);	// Transfer and Store the return Status
	LOG_INFO("The status code is : %d",i2c_irq_status); // Print the Return Status
	if(i2c_irq_status == i2cTransferDone)
	{

		I2C_Transfer_Complete_Flag = 0x30;	//Send external signal upon completion of I2C transfer
		gecko_external_signal(I2C_Transfer_Complete_Flag);
	}
	else if(i2c_irq_status != i2cTransferInProgress)
	{
		LOG_ERROR( "I2C Error: %d",i2c_irq_status);
		I2C_Transfer_Error_Flag = 0x11;
		gecko_external_signal(I2C_Transfer_Error_Flag);	//Send external signal upon transfer error
	}
	CORE_ATOMIC_IRQ_ENABLE();
}






