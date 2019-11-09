#include <stdbool.h>
#include "native_gecko.h"
#include "log.h"
#include "gpio.h"
#include "display.h"
#include "letimer0.h"
extern void gecko_main_init();
bool mesh_bgapi_listener(struct gecko_cmd_packet *evt);
extern void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt);

#define INCLUDE_LOG_DEBUG 1
#define INCLUDE_LOG_INFO 1

int main(void)
{

  // Initialize stack
  gecko_main_init();

  logInit();

  gpioInit();

  displayInit();

  LETIMER_CONFIG_START();

  /* Infinite loop */
  while (1) {
	//displayPrintf(DISPLAY_ROW_CONNECTION,"Deleted All bondings");
	struct gecko_cmd_packet *evt = gecko_wait_event();
	bool pass = mesh_bgapi_listener(evt);
	if (pass) {
		handle_gecko_event(BGLIB_MSG_ID(evt->header), evt);
	}
  };
}
