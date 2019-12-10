
/*
 * 	main.c
 *
 *  Created on: Sep 25, 2019
 *      Author: SURAJ THITE
 */


#include <stdbool.h>
#include "native_gecko.h"
#include "log.h"
#include "gpio.h"
#include "display.h"
#include "letimer0.h"
#include "state_machine.h"
#include "i2c_interrupt.h"
#include "main.h"
extern void gecko_main_init();
bool mesh_bgapi_listener(struct gecko_cmd_packet *evt);
extern void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt);

#define INCLUDE_LOG_DEBUG 1
#define INCLUDE_LOG_INFO 1


int main(void)
{

  // Initialize stack
  gecko_main_init();

  //Initialize the logging functionality
  logInit();

  //Initialize the GPIO configuration
  gpioInit();

  //Initialize the LCD Display functionality
  displayInit();

  //Initialize the LE TIMER configuration and start the timer
  LETIMER_CONFIG_START();

  //Initialize the I2C module
  i2c_int_init();
#if LPM_ENABLE ==1
  GPIO_PinOutClear(WAKE_PIN_PORT,WAKE_PIN); //initially making the CCS811 sensor on.
#endif
  timerWaitUs(80);
  GPIO_PinOutSet(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN);

  LOG_INFO("*********SENSOR CONFIG********");
  //Read and update the status register and configure it to firmware mode.
  CCS811_config();

  LOG_INFO("*********CHANGE MODE********");
  //Change mode of the sensor to MEAS mode
  CCS81_change_mode();
#if LPM_ENABLE ==1
  GPIO_PinOutSet(WAKE_PIN_PORT,WAKE_PIN); //Turning sensor Off for LPM.
#endif
//Set Initial state to configured and event to null_event
  Prev_State = configured;
  event = null_event;

  while (1)
  {
	struct gecko_cmd_packet *evt = gecko_wait_event();
	bool pass = mesh_bgapi_listener(evt);
	if (pass)
	{
		handle_gecko_event(BGLIB_MSG_ID(evt->header), evt);

	}
#if (INTERRUPTS_DISABLED == 0)
	state_machine_1();	//Run state machine model to execute if Interrupts are enabled
#endif
  }
  return 0;

}
