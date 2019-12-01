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
#include "src/gecko_ble_errors.h"
/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/
extern uint8_t push_button0;  //Status for Push Button Zero
extern uint8_t push_button1;  //Status for Push Button One
extern uint32_t PB_flag;	//Flag for external signal from PB0
extern uint32_t PB_flag1;	//Flag for external signal from PB0
/***********************************************************************************************//**
 * @addtogroup app
 * @{
 **************************************************************************************************/

// bluetooth stack heap
#define MAX_CONNECTIONS 2
#define RESET_SW_TIMER_HANDLE (0x10)
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS) + BTMESH_HEAP_SIZE + 1760];

// Bluetooth advertisement set configuration
//
// At minimum the following is required:
// * One advertisement set for Bluetooth LE stack (handle number 0)
// * One advertisement set for Mesh data (handle number 1)
// * One advertisement set for Mesh unprovisioned beacons (handle number 2)
// * One advertisement set for Mesh unprovisioned URI (handle number 3)
// * N advertisement sets for Mesh GATT service advertisements
// (one for each network key, handle numbers 4 .. N+3)
//
#define MAX_ADVERTISERS (4 + MESH_CFG_MAX_NETKEYS)

#define PB0_BUTTON_PORT	(gpioPortF)	//PB0 PORT
#define PB0_BUTTON_PIN 	(6)  //PB0 PIN
#define PB1_BUTTON_PORT	(gpioPortF) //PB1 PORT
#define PB1_BUTTON_PIN	(7) //PB1 PIN
#define PB0_ON        (0x01) //ON STATUS  FOR PB0
#define PB0_OFF       (0x00) //OFF STATUS FOR PB0


uint8_t PBState;

static gecko_bluetooth_ll_priorities linklayer_priorities = GECKO_BLUETOOTH_PRIORITIES_DEFAULT;

// bluetooth stack configuration
extern const struct bg_gattdb_def bg_gattdb_data;

// Flag for indicating DFU Reset must be performed
uint8_t boot_to_dfu = 0;
void set_device_name(bd_addr *pAddr);
void on_off_request_cb(uint16_t model_id,uint16_t element_index, uint16_t client_addr, uint16_t server_addr,uint16_t appkey_index,const struct mesh_generic_request *req, uint32_t transition_ms,uint16_t delay_ms,  uint8_t request_flags);
void on_off_change_cb(uint16_t model_id,uint16_t element_index,const struct mesh_generic_state *current, const struct mesh_generic_state *target, uint32_t remaining_ms);
static void level_change_cb(uint16_t model_id, uint16_t element_index,const struct mesh_generic_state *current, const struct mesh_generic_state *target,  uint32_t remaining_ms);
static void level_request_cb(uint16_t model_id,uint16_t element_index,uint16_t client_addr,uint16_t server_addr, uint16_t appkey_index,const struct mesh_generic_request *request,uint32_t transition_ms,uint16_t delay_ms,uint8_t request_flags);
void gecko_bgapi_classes_init_client_lpn(void);
uint8_t transaction_id =0;
uint8_t transaction_id1 =0;



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

void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt);
void mesh_native_bgapi_init(void);
bool mesh_bgapi_listener(struct gecko_cmd_packet *evt);

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

//void models_init()
//{
//	mesh_lib_generic_server_register_handler(MESH_GENERIC_ON_OFF_SERVER_MODEL_ID,0, on_off_request_cb,on_off_change_cb);
//	mesh_lib_generic_server_register_handler(MESH_GENERIC_LEVEL_SERVER_MODEL_ID,0, level_request_cb,level_change_cb);
//};
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

		if (GPIO_PinInGet(PB0_BUTTON_PORT, PB0_BUTTON_PIN) == 0 || GPIO_PinInGet(PB1_BUTTON_PORT, PB1_BUTTON_PIN) == 0)	//Check whether PB0 or PB1 is pressed during boot
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
			LOG_INFO("Boot Completed");

			//LOAD PERSISTANT DATA

			/*
			 * Persistant deta commands here for flashLoad();
			 */
		}
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
//			mesh_lib_init(malloc,free,8);
//			//Client  Init
//			gecko_cmd_mesh_generic_client_init();
//			//mesh_lib_generic_server_register_handler(MESH_GENERIC_ON_OFF_SERVER_MODEL_ID,0, on_off_request_cb,on_off_change_cb);
//			//Initialize LPN
//			gecko_cmd_mesh_lpn_init();
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
			//System Reset
			break;

		case gecko_evt_mesh_lpn_friendship_terminated_id:
			LOG_INFO("FRIENDSHIP TERMINATED");
			displayPrintf(DISPLAY_ROW_LPN, "UNFRIENDED");
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

			if (((evt->data.evt_system_external_signal.extsignals) & PB_flag1) != 0)
			{
				LOG_INFO("PB1 external Signal");
				struct mesh_generic_state req1;
				req1.kind= mesh_generic_state_level;
				uint16 resp;
				if (push_button1)	//Store the status of PB1
					req1.level.level=100;
				else
					req1.level.level=0;
				resp = mesh_lib_generic_client_publish(MESH_GENERIC_LEVEL_CLIENT_MODEL_ID,0,transaction_id1,&req1,0,0,0);
				LOG_INFO("Response for mesh_lib_generic_client_publish : %X",resp);
				transaction_id1++;
				PB_flag1 =0;
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
 * Function Name: client_request_cb()
 * Description:
 * This is a Function for Client Request
 * @Input:uint16_t model_id,uint16_t element_index, uint16_t client_addr, uint16_t server_addr,uint16_t appkey_index,const struct mesh_generic_request *req, uint32_t transition_ms,uint16_t delay_ms,  uint8_t request_flags
 * @Return Type : None
 *******************************************************************************************************/
void on_off_request_cb(uint16_t model_id,uint16_t element_index, uint16_t client_addr, uint16_t server_addr,uint16_t appkey_index,const struct mesh_generic_request *req, uint32_t transition_ms,uint16_t delay_ms,  uint8_t request_flags)
{
	LOG_INFO("Got recived request, data = %d", req->on_off);
	if(req->on_off == 0x01)	//If on Status detected
	{
		LOG_INFO(" ON STATE");	//LOG the values
		displayPrintf(DISPLAY_ROW_TEMPVALUE, "BUTTON PRESSED");	//Print on LCD
	}

	if(req->on_off == 0x00)	//If OFF status is detected
	{
		LOG_INFO(" OFF STATE");	//Log the value
		displayPrintf(DISPLAY_ROW_TEMPVALUE, "BUTTON RELEASED");	//Print on the LCD
	}
}

/*******************************************************************************************************
 * Function Name: server_change_cb()
 * Description:
 * This is a Function for Server Change
 * @Input:uint16_t model_id,uint16_t element_index,const struct mesh_generic_state *current, const struct mesh_generic_state *target, uint32_t remaining_ms
 * @Return Type : None
 *******************************************************************************************************/
void on_off_change_cb(uint16_t model_id,uint16_t element_index,const struct mesh_generic_state *current, const struct mesh_generic_state *target, uint32_t remaining_ms)
{
	LOG_INFO("In on_off__change_cb");
}

static void level_request_cb(uint16_t model_id,uint16_t element_index,uint16_t client_addr,uint16_t server_addr, uint16_t appkey_index,const struct mesh_generic_request *request,uint32_t transition_ms,uint16_t delay_ms,uint8_t request_flags)
{
	LOG_INFO("In level_change_cb");
	if(request->level >= 50)
	{
		displayPrintf(DISPLAY_ROW_TEMPVALUE,"ALERT");
		LOG_INFO("ALERT");
	}
}

static void level_change_cb(uint16_t model_id, uint16_t element_index,const struct mesh_generic_state *current, const struct mesh_generic_state *target,  uint32_t remaining_ms)
{
	LOG_INFO("In level_change_cb");
}













