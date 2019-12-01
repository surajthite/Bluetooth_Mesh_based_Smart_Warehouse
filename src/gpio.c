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
#define	LED0_port   (gpioPortF)
#define LED0_pin	(4)
#define LED1_port   (gpioPortF)
#define LED1_pin    (5)

#define PB0_BUTTON_PORT	(gpioPortF)
#define PB0_BUTTON_PIN 	(6)
#define PB1_BUTTON_PORT	(gpioPortF)
#define PB1_BUTTON_PIN	(7)

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

	GPIO_PinModeSet(LCD_PORT_EXTCOMIN,LCD_PIN_EXTCOMIN, gpioModePushPull, false);
	GPIO_PinModeSet(PB0_BUTTON_PORT, PB0_BUTTON_PIN, gpioModeInputPull, true);
	GPIO_PinModeSet(PB1_BUTTON_PORT,PB1_BUTTON_PIN, gpioModeInputPull, true);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);	//Enable NVIC
	NVIC_EnableIRQ(GPIO_ODD_IRQn);	//Enable NVIC
	GPIO_IntClear(GPIO_IntGet()); //Clear Interrupt
	GPIO_IntConfig(PB0_BUTTON_PORT,PB0_BUTTON_PIN,true,true,true); //Configure GPIO interrupt with Rising and Falling edges.
	GPIO_IntConfig(PB1_BUTTON_PORT,PB1_BUTTON_PIN,true,true,true); //Configure GPIO interrupt with Rising and Falling edges.
}


/******************************************
 * Function Name: gpioEnableDisplay()
 *
 * This function sets the gpio pin of the LCD for display.
 *@input : None
 *@return:None
 ******************************************/

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


void GPIO_EVEN_IRQHandler()
{
	CORE_ATOMIC_IRQ_DISABLE();
	static int temp_int;
	temp_int = GPIO_IntGet();
	GPIO_IntClear(temp_int);
	push_button0 ^=1;	//Change the status of the pushbutton0
	LOG_INFO("Entered : %d \n",push_button0);
	PB_flag |=0x11;
	gecko_external_signal(PB_flag);	//External signale to gecko
	CORE_ATOMIC_IRQ_ENABLE();
}

void GPIO_ODD_IRQHandler()
{
	CORE_ATOMIC_IRQ_DISABLE();
	static int temp_int;
	temp_int = GPIO_IntGet();
	GPIO_IntClear(temp_int);
	push_button1 ^=1;	//Change the status of the pushbutton0
	LOG_INFO("Entered PB1: %d \n",push_button1);
	PB_flag1 |=0x12;
	gecko_external_signal(PB_flag1);	//External signale to gecko
	CORE_ATOMIC_IRQ_ENABLE();
}
