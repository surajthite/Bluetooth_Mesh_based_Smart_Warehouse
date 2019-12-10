/***************************************************************************//**
 * @file
 * @brief Silicon Labs BT Mesh Empty Example Project
 * This example demonstrates the bare minimum needed for a Blue Gecko BT Mesh C application.
 * The application starts unprovisioned Beaconing after boot
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/* Board headers */
#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"
#include "ble-configuration.h"
#include "board_features.h"

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include <gecko_configuration.h>
#include <mesh_sizes.h>
#include "mesh_generic_model_capi_types.h"
/* Libraries containing default Gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
#include <em_gpio.h>

/* Device initialization header */
#include "hal-config.h"

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif
#include "src/ble_mesh_device_type.h"
#include "src/display.h"
#include "src/gpio.h"
#include "src/main.h"
#include "src/gecko_ble_errors.h"
#include "src/i2c_interrupt.h"
#include "src/state_machine.h"
/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/
extern uint8_t push_button0;  //Status for Push Button Zero
extern uint8_t push_button1;  //Status for Push Button One
extern uint32_t PB_flag;	//Flag for external signal from PB0
extern uint32_t PB_flag1;	//Flag for external signal from PB0
extern uint32_t I2C_Transfer_Complete_Flag;
extern uint32_t I2C_Transfer_Error_Flag;
extern events event;
/***********************************************************************************************//**
 * @addtogroup app
 * @{
 **************************************************************************************************/

// bluetooth stack heap
#define MAX_CONNECTIONS 2
#define RESET_SW_TIMER_HANDLE (0x10)
#define READ_SENSOR (0x30)
#define FIND_FRIEND (0x40)
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS) + BTMESH_HEAP_SIZE + 1760];

#include "gecko_main.h"

uint8_t PBState;

static gecko_bluetooth_ll_priorities linklayer_priorities = GECKO_BLUETOOTH_PRIORITIES_DEFAULT;

// bluetooth stack configuration
extern const struct bg_gattdb_def bg_gattdb_data;

// Flag for indicating DFU Reset must be performed
uint8_t boot_to_dfu = 0;
void set_device_name(bd_addr *pAddr);
void gecko_bgapi_classes_init_client_lpn(void);
static void print_scan_resp(struct gecko_msg_le_gap_scan_response_evt_t *pResp);
void StorePersistentData(uint16_t handle , uint16_t max);
uint16_t LoadPersistentData(uint16_t handle);
void DisplayPersistentData();
void send_ppm_friend(uint16_t ppm_val);
void send_no_of_people_friend(uint16_t val);

uint8_t transaction_id =0;
uint8_t transaction_id1 =0;
uint16_t ppm =0 ;
uint16_t aqi_max;
uint8_t beacon1_flag;
uint8_t beacon2_flag;
uint8_t beacon_count=0;
const gecko_configuration_t config =
{
		.bluetooth.max_connections = MAX_CONNECTIONS,
		.bluetooth.max_advertisers = MAX_ADVERTISERS,
		.bluetooth.heap = bluetooth_stack_heap,
		.bluetooth.heap_size = sizeof(bluetooth_stack_heap) - BTMESH_HEAP_SIZE,
		.bluetooth.sleep_clock_accuracy = 100,
		.bluetooth.linklayer_priorities = &linklayer_priorities,
		.gattdb = &bg_gattdb_data,
		.btmesh_heap_size = BTMESH_HEAP_SIZE,
		.sleep.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
#if (HAL_PA_ENABLE)
		.pa.config_enable = 1, // Set this to be a valid PA config
#if defined(FEATURE_PA_INPUT_FROM_VBAT)
		.pa.input = GECKO_RADIO_PA_INPUT_VBAT, // Configure PA input to VBAT
#else
		.pa.input = GECKO_RADIO_PA_INPUT_DCDC,
#endif // defined(FEATURE_PA_INPUT_FROM_VBAT)
#endif // (HAL_PA_ENABLE)
		.max_timers = 16,
};



/**
 * See light switch app.c file definition
 */
void gecko_bgapi_classes_init_client_lpn(void)
{
	gecko_bgapi_class_dfu_init();
	gecko_bgapi_class_system_init();
	gecko_bgapi_class_le_gap_init();
	gecko_bgapi_class_le_connection_init();
	gecko_bgapi_class_gatt_server_init();
	gecko_bgapi_class_hardware_init();
	gecko_bgapi_class_flash_init();
	gecko_bgapi_class_test_init();
	gecko_bgapi_class_mesh_node_init();
	gecko_bgapi_class_mesh_proxy_init();
	gecko_bgapi_class_mesh_proxy_server_init();
	gecko_bgapi_class_mesh_generic_client_init();
	gecko_bgapi_class_mesh_lpn_init();
}


void lpn_init(void)
{
	uint16_t ret;
	BTSTACK_CHECK_RESPONSE(gecko_cmd_mesh_lpn_init());

	//COnfigure LPN with following parameters
	BTSTACK_CHECK_RESPONSE(gecko_cmd_mesh_lpn_configure(2,6*1000));

	LOG_INFO("Finding friend....");

	ret = gecko_cmd_mesh_lpn_establish_friendship(0)->result;

	if(ret !=0)
	{
		LOG_INFO("Friendship establishment failed with return code %X",ret);
	}
}


/*******************************************************************************************************
 * Function Name: gecko_main_init()
 * Description:
 * This function initializes the gecko for ble mesh operations
 * @Input:None
 * @Return Type : None
 *******************************************************************************************************/
void gecko_main_init()
{
	// Initialize device
	initMcu();
	// Initialize board
	initBoard();
	// Initialize application
	initApp();

	// Minimize advertisement latency by allowing the advertiser to always
	// interrupt the scanner.
	linklayer_priorities.scan_max = linklayer_priorities.adv_min + 1;

	gecko_stack_init(&config);
	//Client Initialization for LPN
	gecko_bgapi_classes_init_client_lpn();
	// Initialize coexistence interface. Parameters are taken from HAL config.
	gecko_initCoexHAL();

}
/*******************************************************************************************************
 * Function Name: handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt)
 * Description:
 * This function handles the various ble mesh stack events.
 * @Input:Pointer to a structure
 * @Return Type : None
 *******************************************************************************************************/
void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt)
{
	switch (evt_id) {
	//System Boot Event
	case gecko_evt_system_boot_id:
		// Initialize Mesh stack in Node operation mode, wait for initialized event

		//	if (GPIO_PinInGet(PB0_BUTTON_PORT, PB0_BUTTON_PIN) == 0 || GPIO_PinInGet(PB1_BUTTON_PORT, PB1_BUTTON_PIN) == 0)	//Check whether PB0 or PB1 is pressed during boot
		if (GPIO_PinInGet(PB0_BUTTON_PORT, PB0_BUTTON_PIN) == 0)
		{
			LOG_INFO("factory reset");
			displayPrintf(DISPLAY_ROW_ACTION, "FACTORY RESET");

			/* perform a factory reset by erasing PS storage. This removes all the keys and other settings
    				that have been configured for this node */
			gecko_cmd_flash_ps_erase_all();
			// reboot after a small delay of 2 sec
			gecko_cmd_hardware_set_soft_timer(2 * 32768,RESET_SW_TIMER_HANDLE, 1); //Software Timer Handle : RESET_SW_TIMER_HANDLE
		}
		else
		{
			gecko_cmd_mesh_node_init();	//Initialize the mesh node
			struct gecko_msg_system_get_bt_address_rsp_t* abc = gecko_cmd_system_get_bt_address();	//Get Bluetooth Address
			set_device_name(&abc->address); //Set device name
			gecko_cmd_mesh_node_set_adv_event_filter(0x7,0,NULL); //Set the advertiising filter to scan the beacons
			LOG_INFO("Boot Completed");
		}
		break;

		//Scan for BLE advertisement packets
	case gecko_evt_le_gap_scan_response_id:
		print_scan_resp(&(evt->data.evt_le_gap_scan_response));	//Function to decode the packet and deduce the count of beacons in vicinity
		break;


		//Software Timer Timeout Event
	case gecko_evt_hardware_soft_timer_id:
		switch (evt->data.evt_hardware_soft_timer.handle)
		{
		case RESET_SW_TIMER_HANDLE:

			gecko_cmd_system_reset(0);	//Factory reset after 2 seconds
			break;

		case LCD_UPDATE:
			displayUpdate(); //1 Hz LCD Update
			break;
		case FIND_FRIEND:
			LOG_INFO("Finding for Friend");
			gecko_cmd_mesh_lpn_establish_friendship(0);
		break;
			//New case to generate event for taking data from sensor
		case READ_SENSOR:
			LOG_INFO("Reading Sensor Value");

#if INTERRUPTS_DISABLED
			ppm=get_ppm();
			if(ppm > aqi_max)
			{
				StorePersistentData(AQI_KEY,ppm);
				aqi_max = ppm;
			}
			send_ppm_friend(ppm);
			displayPrintf(DISPLAY_ROW_PPM,"CO2:%d ppm",ppm);

#else
			event =takereading;
#endif
			//			LOG_INFO("%beacon1_flag : %d",beacon1_flag);
			//			LOG_INFO("%beacon2_flag : %d",beacon2_flag);
			if(beacon1_flag >0)
			{
				beacon_count = beacon_count+1;
				displayPrintf(DISPLAY_ROW_BEACON_STAT, "**Beacon Detected**");
			}
			if(beacon2_flag >0)
			{
				beacon_count = beacon_count+1;
				displayPrintf(DISPLAY_ROW_BEACON_STAT, "**Beacon Detected**");
			}
			LOG_INFO("%No of People: %d",beacon_count);
		//	displayPrintf(DISPLAY_ROW_TEMPVALUE, "ppm: %d beacons: %d",ppm,beacon_count);

			displayPrintf(DISPLAY_ROW_TEMPVALUE, "beacon cnt: %d",beacon_count);
			if(beacon_count == 0)
				displayPrintf(DISPLAY_ROW_BEACON_STAT, " ");
			//Send ppm and count data to friend
			send_no_of_people_friend(beacon_count+1);

			//Store the count in the perisitant storage
			StorePersistentData(BEACONS_KEY,beacon_count);

			//Reset the ppm variable
			ppm = 0;
			//Reset the Global Varibales for scanning
			beacon1_flag =0;
			beacon2_flag =0;
			beacon_count =0;
			LOG_INFO("Checking for Beacons..");
			//Start scanning of Beacons to discover advertising packets
			gecko_cmd_le_gap_set_mode(le_gap_non_discoverable, le_gap_non_connectable);
			gecko_cmd_le_gap_set_scan_parameters(100, 50, 0);
			gecko_cmd_le_gap_discover(le_gap_discover_generic);
			break;
		}

		break;

		//Provisioning started Event
		case gecko_evt_mesh_node_provisioning_started_id:
			displayPrintf(DISPLAY_ROW_ACTION, "Provisioning");
			LOG_INFO("Provisiong Started");
			break;

			//Provisioned Event
		case gecko_evt_mesh_node_provisioned_id:
			displayPrintf(DISPLAY_ROW_ACTION, "Provisioned");
			break;

			//Provisionig Failed Event
		case gecko_evt_mesh_node_provisioning_failed_id:
			displayPrintf(DISPLAY_ROW_ACTION, "Provision Failed");
			LOG_INFO("provisioning failed, code %x", evt->data.evt_mesh_node_provisioning_failed.result);
			// reset
			gecko_cmd_hardware_set_soft_timer(2*32768, RESET_SW_TIMER_HANDLE, 1);	//SET software timer for 2 seconds to reboot
			break;

			//Connection Opened Event
		case gecko_evt_le_connection_opened_id:	//Connection Opened
			LOG_INFO("In connection opened id");
			displayPrintf(DISPLAY_ROW_CONNECTION, "Connected");
			break;

			//Connection Closed Event
		case gecko_evt_le_connection_closed_id:
			LOG_INFO("In connection closed id");
			displayPrintf(DISPLAY_ROW_CONNECTION, " ");
			break;

			//Mesh Node Reset Event
		case gecko_evt_mesh_node_reset_id:	//Reset
			gecko_cmd_hardware_set_soft_timer(2 * 32768,RESET_SW_TIMER_HANDLE , 1);
			break;

			//Clinet Request Event
		case gecko_evt_mesh_generic_server_client_request_id:
			LOG_INFO("In server client request id");
			mesh_lib_generic_server_event_handler(evt);
			break;

			//Server State Changed
		case gecko_evt_mesh_generic_server_state_changed_id:
			LOG_INFO("In server state changed id");
			mesh_lib_generic_server_event_handler(evt);
			break;

			//Enters this event upon sucessful establishment of friendship
		case gecko_evt_mesh_lpn_friendship_established_id:
			LOG_INFO("Friendship established");
			displayPrintf(DISPLAY_ROW_LPN, "LPN EST.");
			break;

		case gecko_evt_mesh_lpn_friendship_failed_id:
			LOG_INFO("friendship failed");
			displayPrintf(DISPLAY_ROW_LPN, "FRIENDSHIP-FAILED");
			gecko_cmd_hardware_set_soft_timer(3*32768, FIND_FRIEND, 0);
			//System Reset
			break;

		case gecko_evt_mesh_lpn_friendship_terminated_id:
			LOG_INFO("FRIENDSHIP TERMINATED");
			displayPrintf(DISPLAY_ROW_LPN, "UNFRIENDED");
			gecko_cmd_hardware_set_soft_timer(3*32768, FIND_FRIEND, 0);
			//Sytem Reset using hardware timer
			break;

		case gecko_evt_system_external_signal_id:


						if (((evt->data.evt_system_external_signal.extsignals) & PB_flag) != 0)
						{
							LOG_INFO("PB0 external Signal");
							struct mesh_generic_request req;
							uint16 resp;
							req.kind= mesh_generic_request_on_off;
							if (push_button0)	//Store the status of PB0
								req.on_off=0x01;
							else
								req.on_off=0x00;

							resp = mesh_lib_generic_client_publish(MESH_GENERIC_ON_OFF_CLIENT_MODEL_ID,0,transaction_id,&req,0,0,0);	//Publish the state of the push button 0.
							LOG_INFO("Response for mesh_lib_generic_client_publish : %X",resp);
							transaction_id++;		//increment transaction Id
							PB_flag =0;
						}
			if (((evt->data.evt_system_external_signal.extsignals) & I2C_Transfer_Complete_Flag) != 0)
			{
				LOG_INFO("I2C transfer complete external Signal");
				event =transfer_complete;
				I2C_Transfer_Complete_Flag = 0x00;
			}

			if (((evt->data.evt_system_external_signal.extsignals) & I2C_Transfer_Error_Flag) != 0)
			{
				event =transfer_error;
				I2C_Transfer_Error_Flag = 0x00;
			}

			if((evt->data.evt_system_external_signal.extsignals) & DATA_READY)
			{
				event = takereading;

			}
			break;


		case gecko_evt_mesh_node_initialized_id:
			gecko_cmd_mesh_generic_client_init();	//Client init
			LOG_INFO("Inside Mesh node Initialied Id");
			if (evt->data.evt_mesh_node_initialized.provisioned)	//if node is provisioned
			{

				LOG_INFO("Device Provisioned");
				mesh_lib_init(malloc,free,8);
				lpn_init();
				displayPrintf(DISPLAY_ROW_ACTION, "PROVISIONED");
				DisplayPersistentData();
				gecko_cmd_hardware_set_soft_timer(5 * 32768, READ_SENSOR, 0);
			}

			if (!evt->data.evt_mesh_node_initialized.provisioned)
			{
				// The Node is now initialized, start un	provisioned Beaconing using PB-ADV and PB-GATT Bearers
				gecko_cmd_mesh_node_start_unprov_beaconing(0x3);
				LOG_INFO("Provisioning Failed");
				gecko_cmd_mesh_node_start_unprov_beaconing(0x3);
				displayPrintf(DISPLAY_ROW_ACTION, "UNPROVISIONED");

			}
			break;
		case gecko_evt_gatt_server_user_write_request_id:
			if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
				/* Set flag to enter to OTA mode */
				boot_to_dfu = 1;
				/* Send response to Write Request */
				gecko_cmd_gatt_server_send_user_write_response(evt->data.evt_gatt_server_user_write_request.connection,
						gattdb_ota_control,
						bg_err_success);

				/* Close connection to enter to DFU OTA mode */
				gecko_cmd_le_connection_close(evt->data.evt_gatt_server_user_write_request.connection);
			}
			break;
		default:
			break;
	}
}

/*******************************************************************************************************
 * Function Name: set_device_name(bd_addr *pAddr)
 * Description:
 * This function sets the unique device name and writes it as an attribute value to the gatt server.
 * @Input:Pointer
 * @Return Type : None
 *******************************************************************************************************/
void set_device_name(bd_addr *pAddr)
{

	char name[20];
	uint16 res;
#if (DEVICE_IS_ONOFF_PUBLISHER ==1)	//If Publisher Print 5823 Publisher
	sprintf(name, "5823Pub%02x:%02x", pAddr->addr[1], pAddr->addr[0]);
	displayPrintf(DISPLAY_ROW_NAME, "%s", name);
#else
	sprintf(name, "5823Sub%02x:%02x", pAddr->addr[1], pAddr->addr[0]);	//If subscriber print 5823 subscriber
	displayPrintf(DISPLAY_ROW_NAME, "%s", name);

#endif
	//Print the device ID
	displayPrintf(DISPLAY_ROW_BTADDR, " %x:%x:%x:%x:%x:%x", pAddr-> addr[5], pAddr-> addr[4], pAddr-> addr[3], pAddr-> addr[2], pAddr-> addr[1], pAddr-> addr[0]);	//Print the address on the LCD Screen
	//Write Data to GATT server
	res = gecko_cmd_gatt_server_write_attribute_value(gattdb_device_name, 0, strlen(name), (uint8 *)name)->result;
}


/*******************************************************************************************************
 * Function Name: print_scan_resp(struct gecko_msg_le_gap_scan_response_evt_t *pResp)
 * Descrtipiton : This function  decodes the advertising packets and segregtes them on the basis of UUID and
 * last byte of address of the beacon
 * @input:packet structure
 * @Return : None
 *******************************************************************************************************/
static void print_scan_resp(struct gecko_msg_le_gap_scan_response_evt_t *pResp)
{
	const uint8 proxy_UUID[2] ={0x06,0x1a};	//Array to store UUID data of the beacons
	int i =0;
	int ad_match_found=0;
	int ad_len;
	int ad_type;

	while (i< pResp->data.len -1)	//Iterate through end the packet
	{
		ad_len = pResp->data.data[i];	//Set length as first byte
		ad_type =pResp->data.data[i+1];	//Set type of packet from the seond byte of the packet

		{
			if(memcmp(proxy_UUID , &(pResp->data.data[i+2]),2)==0)	//If UUID found then increment the count
			{
				ad_match_found = ad_match_found + 1;
			}
		}
		i = i + 1 + ad_len;
	}

	if(ad_match_found > 0)	//If UUID found
	{
		for (i=5;i>=0;i--)
		{
			//		LOG_INFO("%2.2x",pResp->address.addr[i]);	//Print the address
			if(i==0)
			{
				if(pResp->address.addr[i] == 0x76)	//Compare for last byte of the hardware address recieved and update the beacon flags
					beacon2_flag++;
				if(pResp->address.addr[i] == 0x92)
					beacon1_flag++;

			}
		}
		//	LOG_INFO(",RSSI : %d \r\n",pResp->rssi);	//Print the RSSI Values
	}

}

/*******************************************************************************************************
 * Function Name:void StorePersistentData(uint16_t handle , uint16_t max)
 * Descrtipiton : This function  stores the persistant data to the location pointed by the handle
 * @input:packet structure
 * @Return : None
 *******************************************************************************************************/
void StorePersistentData(uint16_t handle , uint16_t max)
{
	int res;
	uint8_t * val;
	val =&max;
	res=gecko_cmd_flash_ps_save(handle, sizeof(max),val)->result;
	LOG_INFO("%s in store persistent data (returned %d)",res==0 ? "Success" : "Error",res);
}
/*******************************************************************************************************
 * Function Name: uint16_t LoadPersistentData(uint16_t handle)
 * Descrtipiton : This function  loads the perisistant data upon the handle passed through it and mem copies
 * it to the variable
 * @input:packet structure
 * @Return : None
 *******************************************************************************************************/

uint16_t LoadPersistentData(uint16_t handle)
{
	uint16_t data;
	struct gecko_msg_flash_ps_load_rsp_t* resp;
	resp=(gecko_cmd_flash_ps_load(handle));
	memcpy(&data,&resp->value.data,resp->value.len);
	LOG_INFO("Persistent data is %d",data);
	return data;
}
/*******************************************************************************************************
 * Function Name: void DisplayPersistentData()
 * Descrtipiton : This function  displays the persistant data on the LCD screen
 * @input:void
 * @Return :void
 *******************************************************************************************************/
void DisplayPersistentData()
{
	uint16_t persistent_data_ppm;
	uint16_t persisent_data_count;
	persistent_data_ppm=LoadPersistentData(AQI_KEY);
	persisent_data_count =LoadPersistentData(BEACONS_KEY);
	displayPrintf(DISPLAY_ROW_PERSISTANT,"P.DATA: AQI:%d C:%d",persistent_data_ppm,persisent_data_count);
	//displayPrintf(10,"AQI %d",persistent_data);
	LOG_INFO("AQI %d Beacon-Count %d",persistent_data_ppm,persisent_data_count);
}
/*******************************************************************************************************
 * Function Name: void send_no_of_people_friend(uint16_t val)
 * Descrtipiton : This function updates the friend with the change in the beacon value detected
 * @input:no of beacons detected
 * @Return : None
 *******************************************************************************************************/
void send_no_of_people_friend(uint16_t val)
{
	struct mesh_generic_state req1;
	req1.kind= mesh_generic_state_level;
	uint16 resp;
	req1.level.level=val;
	resp = mesh_lib_generic_client_publish(MESH_GENERIC_LEVEL_CLIENT_MODEL_ID,0,transaction_id1,&req1,0,0,0);
	LOG_INFO("Response for send_no_of_people_friend : %X",resp);
	transaction_id1++;
}
/*******************************************************************************************************
 * Function Name: void send_ppm_friend(uint16_t ppm_val)
 * Descrtipiton : This function  sends the ppm value (whether fire detection threshold is reached) to the friend
 * @input: ppm value
 * @Return : None
 *******************************************************************************************************/
void send_ppm_friend(uint16_t ppm_val)
{
	struct mesh_generic_request req;
	uint16 resp;
	req.kind= mesh_generic_request_on_off;
	if (ppm_val > FIRE_DETECTED_PPM)//Check for Fire Detection Condition
		req.on_off=0x01;
	else
		req.on_off=0x00;

	resp = mesh_lib_generic_client_publish(MESH_GENERIC_ON_OFF_CLIENT_MODEL_ID,0,transaction_id,&req,0,0,0);	//Publish the state of the push button 0.
	LOG_INFO("Response for send_ppm_friend : %X",resp);
	transaction_id++;		//increment transaction Id
}
