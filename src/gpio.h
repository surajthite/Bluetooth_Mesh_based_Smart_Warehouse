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
#define GPIO_DISPLAY_SUPPORT_IMPLEMENTED (1)
#define GPIO_SET_DISPLAY_EXT_COMIN_IMPLEMENTED (1)



void gpioInit();
void gpioEnableDisplay();
void gpioSetDisplayExtcomin(bool high);
#endif /* SRC_GPIO_H_ */
