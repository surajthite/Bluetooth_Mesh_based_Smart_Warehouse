

/*HEADER FILE FOR INTERRUPT HANDLING OF I2C
 * i2c_interrupt.h
 *
 *  Created on: Sep 25, 2019
 *      Author: SURAJ THITE
 */

#ifndef SRC_I2C_INTERRUPT_H_
#define SRC_I2C_INTERRUPT_H_

#include "i2cspm.h"
//#include "em_i2c.c"
#include "em_i2c.h"
#include "gpio.h"
#include "core_cm4.h"
#include "main.h"
#include "infrastructure.h"
#include "native_gecko.h"
#include"log.h"
#include "display.h"
#include "sleep.h"
void i2c_int_init();
void Interrupt_write_data();
void Interrupt_read_data();
void temp_data_print();
void Temperature_calculation_for_BLE(void);
#define INCLUDE_LOG_DEBUG 1
#define INCLUDE_LOG_INFO 1




#endif /* SRC_I2C_INTERRUPT_H_ */




