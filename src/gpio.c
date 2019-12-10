/*
 * gpio.c
 *
 *  Created on: Dec 12, 2018
 *      Author: Dan Walkes
 */
#include "gpio.h"
/**
 * TODO: define these.  See the radio board user guide at https://www.silabs.com/documents/login/user-guides/ug279-brd4104a-user-guide.pdf
 * and GPIO documentation at https://siliconlabs.github.io/Gecko_SDK_Doc/efm32g/html/group__GPIO.html
 */


uint8_t push_button0=0;
uint8_t push_button1=0;
uint32_t PB_flag=0;
uint32_t PB_flag1=0;

/*******************************************************************************************************
 * Function Name: gpioInit()
 * Function to initialize the gpio pins for Load power Management.
 *******************************************************************************************************/


void gpioInit()
{

	GPIO_PinModeSet(LCD_PORT_EXTCOMIN,LCD_PIN_EXTCOMIN, gpioModePushPull, false);	//Initialize the LDC port and Pin

	GPIO_PinModeSet(PB0_BUTTON_PORT, PB0_BUTTON_PIN, gpioModeInputPull, true);	//Initialize the PB0 port and Pin for sending emergency fire alarm signal

	GPIO_PinModeSet(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN, gpioModePushPull, false);

	GPIO_PinModeSet(WAKE_PIN_PORT, WAKE_PIN, gpioModePushPull, false);

	//GPIO_PinOutClear(WAKE_PIN_PORT,WAKE_PIN);

	NVIC_EnableIRQ(GPIO_EVEN_IRQn);	//Enable NVIC

	GPIO_IntClear(GPIO_IntGet()); //Clear Interrupt

	GPIO_IntConfig(PB0_BUTTON_PORT,PB0_BUTTON_PIN,true,true,true); //Configure GPIO interrupt with Rising and Falling edges.
}


/******************************************************************************************************
 * Function Name: gpioEnableDisplay()
 *
 * This function sets the gpio pin of the LCD for display.
 *@input : None
 *@return:None
 ****************************************************************************************************/

void gpioEnableDisplay()
{
	GPIO_PinOutSet(LCD_PORT_DISP_SEL,LCD_PIN_DISP_SEL);
}

/******************************************
 * Function Name: gpioSetDisplayExtcomin(bool high)
 *
 * This function changes the state of the pin  w.r.t. the passed boolean vlaue.
 *@input : Bool
 *@return:None
 ******************************************/

void gpioSetDisplayExtcomin(bool high)
{
	if (high == false)
	{
		GPIO_PinOutClear(LCD_PORT_EXTCOMIN,LCD_PIN_EXTCOMIN);
	}
	if (high == true)
	{
		GPIO_PinOutSet(LCD_PORT_EXTCOMIN,LCD_PIN_EXTCOMIN);
	}

}

/*******************************************************************************************************
 * Function Name: void GPIO_EVEN_IRQHandler()
 * IRQ handler for PB0 gpio
 *******************************************************************************************************/

void GPIO_EVEN_IRQHandler()
{
	CORE_ATOMIC_IRQ_DISABLE();	//Enter Critical Region
	static int temp_int;
	temp_int = GPIO_IntGet();
	GPIO_IntClear(temp_int);	//Disable Interrupt
	push_button0 ^=1;	//Change the status of the pushbutton0 (For fire alarm)
	LOG_INFO("Entered : %d \n",push_button0);
	PB_flag |=0x11;
	gecko_external_signal(PB_flag);	//External signale to gecko BLE Stack
	CORE_ATOMIC_IRQ_ENABLE();
}

/*******************************************************************************************************
 * Function Name: void GPIO_ODD_IRQHandler()
 * IRQ handler for INT pin of sensor
 *******************************************************************************************************/
void GPIO_ODD_IRQHandler()
{
	CORE_ATOMIC_IRQ_DISABLE();
	event = takereading;	//Change Event to take PPM reading from the sensor
	CORE_ATOMIC_IRQ_ENABLE();
}
/*******************************************************************************************************
 * Function Name: void en_i2c()
 * Function to enable i2c pin
 *******************************************************************************************************/
void en_i2c()
{
	GPIO_PinOutSet(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN);	//Enable I2C
}
/*******************************************************************************************************
 * Function Name: void dis_i2c()
 * Function to disbale i2c pin
 *******************************************************************************************************/
void dis_i2c()
{
	GPIO_PinOutClear(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN);	//Disable I2C
}

