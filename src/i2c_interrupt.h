

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
void Interrupt_write_data( I2C_TransferSeq_TypeDef init, uint16_t len);
uint16_t Interrupt_read_data(I2C_TransferSeq_TypeDef init, uint16_t len);
void Interrupt_write_read();
#define INCLUDE_LOG_DEBUG 1
#define INCLUDE_LOG_INFO 1
void Interrupt_write();
void calculate_ppm();
void Disable_I2C_Interrupts();
void Enable_I2C_Interrupts();


#endif /* SRC_I2C_INTERRUPT_H_ */




