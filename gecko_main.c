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

/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/
extern uint8_t push_button0;
extern uint32_t PB_flag;
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

#define PB0_BUTTON_PORT	(gpioPortF)
#define PB0_BUTTON_PIN 	(6)
#define PB1_BUTTON_PORT	(gpioPortF)
#define PB1_BUTTON_PIN	(7)
#define PB0_ON        (0x01)
#define PB0_OFF       (0x00)

#define PB0_FLASH_ADDR  (0x4003)
#define PB_FLASH_ID    (0x03)

uint8_t PBState;

static gecko_bluetooth_ll_priorities linklayer_priorities = GECKO_BLUETOOTH_PRIORITIES_DEFAULT;

// bluetooth stack configuration
extern const struct bg_gattdb_def bg_gattdb_data;

// Flag for indicating DFU Reset must be performed
uint8_t boot_to_dfu = 0;
void set_device_name(bd_addr *pAddr);
void client_request_cb(uint16_t model_id,uint16_t element_index, uint16_t client_addr, uint16_t server_addr,uint16_t appkey_index,const struct mesh_generic_request *req, uint32_t transition_ms,uint16_t delay_ms,  uint8_t request_flags);
void server_change_cb(uint16_t model_id,uint16_t element_index,const struct mesh_generic_state *current, const struct mesh_generic_state *target, uint32_t remaining_ms);

uint8_t transaction_id =0;



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
void gecko_bgapi_classes_init_server_friend(void)
{
	gecko_bgapi_class_dfu_init();
	gecko_bgapi_class_system_init();
	gecko_bgapi_class_le_gap_init();
	gecko_bgapi_class_le_connection_init();
	//gecko_bgapi_class_gatt_init();
	gecko_bgapi_class_gatt_server_init();
	gecko_bgapi_class_hardware_init();
	gecko_bgapi_class_flash_init();
	gecko_bgapi_class_test_init();
	//gecko_bgapi_class_sm_init();
	//mesh_native_bgapi_init();
	gecko_bgapi_class_mesh_node_init();
	//gecko_bgapi_class_mesh_prov_init();
	gecko_bgapi_class_mesh_proxy_init();
	gecko_bgapi_class_mesh_proxy_server_init();
	//gecko_bgapi_class_mesh_proxy_client_init();
	//gecko_bgapi_class_mesh_generic_client_init();
	gecko_bgapi_class_mesh_generic_server_init();
	//gecko_bgapi_class_mesh_vendor_model_init();
	//gecko_bgapi_class_mesh_health_client_init();
	//gecko_bgapi_class_mesh_health_server_init();
	//gecko_bgapi_class_mesh_test_init();
	gecko_bgapi_class_mesh_lpn_init();
	//gecko_bgapi_class_mesh_friend_init();
}


/**
 * See main function list in soc-btmesh-switch project file
 */
void gecko_bgapi_classes_init_client_lpn(void)
{
	gecko_bgapi_class_dfu_init();
	gecko_bgapi_class_system_init();
	gecko_bgapi_class_le_gap_init();
	gecko_bgapi_class_le_connection_init();
	//gecko_bgapi_class_gatt_init();
	gecko_bgapi_class_gatt_server_init();
	gecko_bgapi_class_hardware_init();
	gecko_bgapi_class_flash_init();
	gecko_bgapi_class_test_init();
	//gecko_bgapi_class_sm_init();
	//mesh_native_bgapi_init();
	gecko_bgapi_class_mesh_node_init();
	//gecko_bgapi_class_mesh_prov_init();
	gecko_bgapi_class_mesh_proxy_init();
	gecko_bgapi_class_mesh_proxy_server_init();
	//gecko_bgapi_class_mesh_proxy_client_init();
	gecko_bgapi_class_mesh_generic_client_init();
	//gecko_bgapi_class_mesh_generic_server_init();
	//gecko_bgapi_class_mesh_vendor_model_init();
	//gecko_bgapi_class_mesh_health_client_init();
	//gecko_bgapi_class_mesh_health_server_init();
	//gecko_bgapi_class_mesh_test_init();
	gecko_bgapi_class_mesh_lpn_init();
	//gecko_bgapi_class_mesh_friend_init();

}
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

	if( DeviceUsesClientModel() ) {
		gecko_bgapi_classes_init_client_lpn();
	} else {
		gecko_bgapi_classes_init_server_friend();
	}

	// Initialize coexistence interface. Parameters are taken from HAL config.
	gecko_initCoexHAL();

}

void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt)
{
	switch (evt_id) {
	case gecko_evt_system_boot_id:
		// Initialize Mesh stack in Node operation mode, wait for initialized event

		if (GPIO_PinInGet(PB0_BUTTON_PORT, PB0_BUTTON_PIN) == 0 || GPIO_PinInGet(PB1_BUTTON_PORT, PB1_BUTTON_PIN) == 0)
		{
			LOG_INFO("factory reset");
			displayPrintf(DISPLAY_ROW_ACTION, "FACTORY RESET");

			/* perform a factory reset by erasing PS storage. This removes all the keys and other settings
    				that have been configured for this node */
			gecko_cmd_flash_ps_erase_all();
			// reboot after a small delay of 2 sec
			gecko_cmd_hardware_set_soft_timer(2 * 32768,RESET_SW_TIMER_HANDLE, 1);
		}
		else
		{
			gecko_cmd_mesh_node_init();
			struct gecko_msg_system_get_bt_address_rsp_t* abc = gecko_cmd_system_get_bt_address();
			set_device_name(&abc->address);
			LOG_INFO("Boot Completed");
		}
		break;


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


		case gecko_evt_mesh_node_provisioning_started_id:
			displayPrintf(DISPLAY_ROW_ACTION, "Provisioning");
			LOG_INFO("Provisiong Started");
			break;


		case gecko_evt_mesh_node_provisioned_id:
			displayPrintf(DISPLAY_ROW_ACTION, "Provisioned");
			break;


		case gecko_evt_mesh_node_provisioning_failed_id:
			displayPrintf(DISPLAY_ROW_ACTION, "Provision Failed");
			LOG_INFO("provisioning failed, code %x", evt->data.evt_mesh_node_provisioning_failed.result);
			// reset
			gecko_cmd_hardware_set_soft_timer(2*32768, RESET_SW_TIMER_HANDLE, 1);
			break;

		case gecko_evt_le_connection_opened_id:
			LOG_INFO("In connection opened id");
			displayPrintf(DISPLAY_ROW_CONNECTION, "Connected");
			break;

		case gecko_evt_le_connection_closed_id:
			LOG_INFO("In connection closed id");
			displayPrintf(DISPLAY_ROW_CONNECTION, " ");
			break;

		case gecko_evt_mesh_node_reset_id:
			gecko_cmd_hardware_set_soft_timer(2 * 32768,RESET_SW_TIMER_HANDLE , 1);
			break;

		case gecko_evt_mesh_generic_server_client_request_id:

			LOG_INFO("In server client request id");

			//			if(DeviceUsesServerModel())
			mesh_lib_generic_server_event_handler(evt);

			break;

		case gecko_evt_mesh_generic_server_state_changed_id:

			LOG_INFO("In server state changed id");

			//			if(DeviceUsesServerModel())
			mesh_lib_generic_server_event_handler(evt);

			break;

		case gecko_evt_system_external_signal_id:

			if (((evt->data.evt_system_external_signal.extsignals) & PB_flag) != 0)
			{
				LOG_INFO("PB0 external Signal");
				struct mesh_generic_request req;
				uint16 resp;
				req.kind= mesh_generic_request_on_off;
				if (!push_button0)
				req.on_off=0x01;
				else
				req.on_off=0x00;

				resp = mesh_lib_generic_client_publish(MESH_GENERIC_ON_OFF_CLIENT_MODEL_ID,0,transaction_id,&req,0,0,0);
				LOG_INFO("Response for mesh_lib_generic_client_publish : %d",resp);
				transaction_id++;
			}
				break;


		case gecko_evt_mesh_node_initialized_id:

			LOG_INFO("Inside Mesh node Initialied Id");
			if (evt->data.evt_mesh_node_initialized.provisioned)
			{
				printf("Device Provisioned");
#if DEVICE_USES_BLE_MESH_CLIENT_MODEL
				struct gecko_msg_mesh_generic_client_init_rsp_t* resp = gecko_cmd_mesh_generic_client_init();
				LOG_INFO(" The response code for gecko_cmd_mesh_generic_client_init is : %d ",resp->result);
#endif

#if DEVICE_USES_BLE_MESH_SERVER_MODEL

				gecko_cmd_mesh_generic_server_init();
#endif


#if DEVICE_IS_ONOFF_PUBLISHER
				errorcode_t response;
				response = mesh_lib_init(malloc, free, 8);
				LOG_INFO(" The response for mesh lib init  is : %d ",response);

#else
				mesh_lib_init(malloc,free,9);
				//mesh_lib_generic_server_register_handler(MESH_GENERIC_ON_OFF_SERVER_MODEL_ID,0,client_request_cb,server_change_cb);
				mesh_lib_generic_server_register_handler(MESH_GENERIC_ON_OFF_SERVER_MODEL_ID,0, client_request_cb,server_change_cb);
				//mesh_lib_generic_server_publish(MESH_GENERIC_ON_OFF_SERVER_MODEL_ID , 0, mesh_generic_state_on_off);
				mesh_lib_generic_server_publish(MESH_GENERIC_LEVEL_SERVER_MODEL_ID,0, mesh_generic_state_on_off);


#endif
			}

			if (!evt->data.evt_mesh_node_initialized.provisioned)
			{
				// The Node is now initialized, start un	provisioned Beaconing using PB-ADV and PB-GATT Bearers
				gecko_cmd_mesh_node_start_unprov_beaconing(0x3);
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
	void set_device_name(bd_addr *pAddr)
	{

		char name[20];
		uint16 res;
#if (DEVICE_IS_ONOFF_PUBLISHER ==1)
		sprintf(name, "5823Pub%02x:%02x", pAddr->addr[1], pAddr->addr[0]);
		displayPrintf(DISPLAY_ROW_NAME, "%s", name);
#else
		sprintf(name, "5823Sub%02x:%02x", pAddr->addr[1], pAddr->addr[0]);
		displayPrintf(DISPLAY_ROW_NAME, "%s", name);
#endif
		//Print the device ID
		displayPrintf(DISPLAY_ROW_BTADDR, " %x:%x:%x:%x:%x:%x", pAddr-> addr[5], pAddr-> addr[4], pAddr-> addr[3], pAddr-> addr[2], pAddr-> addr[1], pAddr-> addr[0]);
		//Write Data to GATT server
		res = gecko_cmd_gatt_server_write_attribute_value(gattdb_device_name, 0, strlen(name), (uint8 *)name)->result;
	}

	void client_request_cb(uint16_t model_id,uint16_t element_index, uint16_t client_addr, uint16_t server_addr,uint16_t appkey_index,const struct mesh_generic_request *req, uint32_t transition_ms,uint16_t delay_ms,  uint8_t request_flags)
	{
		LOG_INFO("Got recived request, data = %d", req->on_off);
		if(req->on_off == 0x01)
		{
			LOG_INFO(" ON STATE");
			displayPrintf(DISPLAY_ROW_ACTION, "BUTTON PRESSED");
		}

		if(req->on_off == 0x00)
		{
			LOG_INFO(" OFF STATE");
			displayPrintf(DISPLAY_ROW_ACTION, "BUTTON RELEASED");
		}
	}
	void server_change_cb(uint16_t model_id,uint16_t element_index,const struct mesh_generic_state *current, const struct mesh_generic_state *target, uint32_t remaining_ms)
	{

	}










