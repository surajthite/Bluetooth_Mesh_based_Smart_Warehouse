/*
 * gpio.h
 *
 *  Created on: Dec 12, 2018
 *      Author: Dan Walkes
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include <stdbool.h>
#include "log.h"
#include "em_core.h"
#include "em_gpio.h"
#include "core_cm4.h"
#include <string.h>
#include "displayls013b7dh03config.h"
#include "system_efr32bg13p.h"
#include "state_machine.h"
#define GPIO_DISPLAY_SUPPORT_IMPLEMENTED (1)
#define GPIO_SET_DISPLAY_EXT_COMIN_IMPLEMENTED (1)

#define	LED0_port   (gpioPortF)
#define LED0_pin	(4)
#define LED1_port   (gpioPortF)
#define LED1_pin    (5)

#define PB0_BUTTON_PORT	(gpioPortF)
#define PB0_BUTTON_PIN 	(6)
#define PB1_BUTTON_PORT	(gpioPortF)
#define PB1_BUTTON_PIN	(7)
#define SENSOR_ENABLE_PIN 15
#define SENSOR_ENABLE_PORT gpioPortD
#define WAKE_PIN_PORT gpioPortF
#define WAKE_PIN 7

void gpioInit();
void gpioEnableDisplay();
void gpioSetDisplayExtcomin(bool high);
void en_i2c();
void dis_i2c();

#endif /* SRC_GPIO_H_ */
