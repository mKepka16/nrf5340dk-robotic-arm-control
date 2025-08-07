#include <zephyr/kernel.h>
#include "advert.h"
#include "connection.h"
#include <zephyr/bluetooth/bluetooth.h>
#include "led.h"
#include <zephyr/logging/log.h>
#include "servo.h"

LOG_MODULE_REGISTER(Main, LOG_LEVEL_WRN);

int main(void)
{
  init_leds();

  init_servos();

  bt_enable(NULL);

  init_advertising();

  init_bt_connection();

  start_advertising();

  return 0;
}
