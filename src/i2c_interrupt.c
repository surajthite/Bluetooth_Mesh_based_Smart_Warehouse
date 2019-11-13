
/*
 * i2c_interrupt.c
 *
 *  Created on: Sep 25, 2019
 *      Author: SURAJ THITE
 */

//Header Files//
#include "i2c_interrupt.h"
#include "gatt_db.h"
//Gloabl Variables//
uint8_t command_temp_sensor = 0xF3;
uint8_t buffer[2];
bool  write_status =0;
bool read_status =0;
I2C_TransferSeq_TypeDef write_config;
I2C_TransferSeq_TypeDef read_config;

float Temperature_Val  = 0;//Temporary variable for temprature calculation

uint32_t Temperature_Calc_flag =0;
uint32_t Setup_temp_timer_flag =0;

/*******************************************************************************************************
 * Function Name: i2c_int_init()
 * Descrtipiton : This function configures and initializes the interrupts for IC0.
 * @input:NOne
 * @Return : None
 *******************************************************************************************************/
void i2c_int_init()
{
	I2CSPM_Init_TypeDef i2c_config_int = I2CSPM_INIT_DEFAULT;	// Set Default
	i2c_config_int.sclPort = gpioPortC;		// SET GPIO PORT C for SCL
	i2c_config_int.sdaPort = gpioPortC;	// SET GPIO Port C for SDA
	i2c_config_int.sclPin = 10;	// SET SCL Pin to 10
	i2c_config_int.sdaPin = 11; //SET SDA Pin to 11
	i2c_config_int.portLocationScl = 14;	// Set SCL Port Location to 14
	i2c_config_int.portLocationSda = 16;	// Set SDA Port Location to 16
	I2CSPM_Init(&i2c_config_int);	//Initalise the i2c with above config
	NVIC_EnableIRQ(I2C0_IRQn); // Enable NVIC Interrupts
	I2C_IntEnable(I2C0,I2C_IEN_RXDATAV | I2C_IEN_RXFULL | I2C_IEN_TXC );// Enable Interrupts for i2C
}

/*******************************************************************************************************
 * Function Name: Interrupt_write_data
 * Desciption:
 * This function configures and write the command to the buff0 and setting up the the write status register.
 * @input: None
 * @reutn :None
 *******************************************************************************************************/

void Interrupt_write_data()
{
	write_config.addr        = 0x80 ;  // Left shifted the address by one bit.
	write_config.flags       = I2C_FLAG_WRITE;
	write_config.buf[0].data = &command_temp_sensor ;//F3 COmmand For sensor read
	write_config.buf[0].len  = 1;
	I2C_TransferInit(I2C0,&write_config);//Init Transfer
	write_status = 1;//UPdate the Flag Value
}
/*******************************************************************************************************
 * Function Name: Interrupt_read_data
 * Description:
 * This function configures and reads from the buffer  while setting up the the read status register.
 * @input: None
 * @Return:None
 *******************************************************************************************************/

void Interrupt_read_data()
{
	read_config.addr        = 0x80 ;	// Left shift the address by one bit
	read_config.flags       = I2C_FLAG_READ;
	read_config.buf[0].data = buffer;
	read_config.buf[0].len  = 1;
	read_config.buf[1].data = buffer;
	read_config.buf[1].len  = 1;
	I2C_TransferInit(I2C0,&read_config);//Initialize the i2c read transfer
	read_status = 1;//Update the read flag
}

/*******************************************************************************************************
 * Function Name: temp_data_print
 * This function caliberates and reads from the buffer  while setting up the the read status register.
 * The real time Values are printed on the serial port via LOG_INFO function.
 *******************************************************************************************************/


void temp_data_print()
{
	int temp1;
	int read_val =0;
	read_val|=((buffer[0]) << 8);//Left Shift the register by 8 bits
	read_val|= buffer[1];
	Temperature_Val = ((175.72*(read_val))/65536) - 46.85;// calculate the temperature value.
	LOG_INFO("Temperature_in_degree_Celsius = %f",Temperature_Val);//at time //%d milli-seconds from startup ",Temperature_Val,loggerGetTimestamp());
	temp1 = (int)Temperature_Val;
	displayPrintf(DISPLAY_ROW_TEMPVALUE,"Temperature:%.2f C",Temperature_Val);
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
		if(write_status == 1)				// If interrupt detected for the write state , Set the event and clear the FLAG.
		{
			//event = Setup_temp_timer;
			write_status = 0; //Clear write Flag

			Setup_temp_timer_flag |=0x04;//Set the external Flag
			gecko_external_signal(Setup_temp_timer_flag);
		}
		if(read_status == 1)
		{
			//event = Temperature_Calc;	// If interrupt detected for the read state , Set the event and clear the FLAG.
			read_status = 0; // Clear Read Flag
			Temperature_Calc_flag |=0x10;//Set the external Flag
			gecko_external_signal(Temperature_Calc_flag);

		}
	}
	else
	{
		switch (i2c_irq_status)	// LOG the error in case of transfer failure.
		{
		case i2cTransferNack:
			LOG_ERROR("\n Received NACK from the sesnor \n");
			break;
		case i2cTransferBusErr:
			LOG_ERROR("\n Bus Error Exist \n");
			break;
		case i2cTransferArbLost:
			LOG_ERROR("\n Bus Arbitration lost \n");
			break;
		case i2cTransferUsageFault:
			LOG_ERROR("\n Usage fault \n");
			break;
		case i2cTransferSwFault:
			LOG_ERROR("\n Software fault \n");
			break;
		}
	}
	CORE_ATOMIC_IRQ_ENABLE();
}

/***********************************************************************************************//**
 * Function name : void Temperature_calculation_for_BLE(void)
 *  \brief  This function is called by the application when the periodic measurement timer expires.
 *  \param[in]  buf  Event message.
 *  \return  length of temp measurement.
 **************************************************************************************************/
void Temperature_calculation_for_BLE(void)
{
	uint16_t Temp_Buffer_BLE[5]; //Temporary buffer
	uint8_t flag =0;
	uint32_t temp_conv; //Variable to store converted temperature
	uint8_t *pointertotempbuff = Temp_Buffer_BLE;	//Pointer to temperature buffer array

	UINT8_TO_BITSTREAM(pointertotempbuff ,flag);	// COnvert uin8 to bitstream
	temp_conv = FLT_TO_UINT32(Temperature_Val * 1000 ,-3); // Convert float value to uint32
	UINT32_TO_BITSTREAM(pointertotempbuff , temp_conv);	//COnverter uint32 value to bistream


//	gecko_cmd_gatt_server_send_characteristic_notification(0xFF , gattdb_temperature_measurement , 5 , Temp_Buffer_BLE); //Send command notification to the BLE client

	//  error=gecko_cmd_gatt_server_send_characteristic_notification(0xFF, gattdb_button_state,2,BTN_BUFF);
}





