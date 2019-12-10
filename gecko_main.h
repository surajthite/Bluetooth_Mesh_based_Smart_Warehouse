/*
 * gecko_main.h
 *
 *  Created on: Dec 8, 2019
 *      Author: AKSHAY THITE
 */

#ifndef GECKO_MAIN_H_
#define GECKO_MAIN_H_


#define MAX_ADVERTISERS (4 + MESH_CFG_MAX_NETKEYS)

#define PB0_BUTTON_PORT	(gpioPortF)	//PB0 PORT
#define PB0_BUTTON_PIN 	(6)  //PB0 PIN
#define PB1_BUTTON_PORT	(gpioPortF) //PB1 PORT
#define PB1_BUTTON_PIN	(7) //PB1 PIN
#define PB0_ON        (0x01) //ON STATUS  FOR PB0
#define PB0_OFF       (0x00) //OFF STATUS FOR PB0
#define AQI_KEY (0X4000)
#define BEACONS_KEY (0X4010)


void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt);
void mesh_native_bgapi_init(void);
bool mesh_bgapi_listener(struct gecko_cmd_packet *evt);
void StorePersistentData(uint16_t handle , uint16_t max);
uint16_t LoadPersistentData(uint16_t handle);
void DisplayPersistentData();
void send_no_of_people_friend(uint16_t val);
void send_ppm_friend(uint16_t ppm_val);
#endif /* GECKO_MAIN_H_ */
