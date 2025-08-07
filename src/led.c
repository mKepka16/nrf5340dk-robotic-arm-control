#include "led.h"
#include <zephyr/kernel.h>
#include <stdbool.h>
#include <dk_buttons_and_leds.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(LED, LOG_LEVEL_WRN);

#define BT_ADVERT_LED DK_LED1
#define BT_CONNECTION_LED DK_LED2
#define ADVERT_LED_BLINK_INTERVAL_MS 400
#define ADVERT_LED_THREAD_PRIORITY 8
#define ADVERT_LED_THREAD_STACK_SIZE 256 

static bool is_adverting = false;
static bool is_advert_led_enabled = false;
K_THREAD_STACK_DEFINE(advert_led_stack, ADVERT_LED_THREAD_STACK_SIZE);
static struct k_thread advert_led_thread;
static k_tid_t advert_led_tid;

void init_leds(void)
{
  dk_leds_init();
  LOG_INF("LEDs initialized\n");
}

static void blink_advert_led(void)
{
  LOG_INF("Advert LED blinking started\n");
  while (1)
  {
    if (!is_adverting)
    {
      break;
    }
    is_advert_led_enabled = !is_advert_led_enabled;
    dk_set_led(BT_ADVERT_LED, is_advert_led_enabled);
    k_msleep(ADVERT_LED_BLINK_INTERVAL_MS);
  }

  is_advert_led_enabled = false;
  dk_set_led(BT_ADVERT_LED, is_advert_led_enabled);
  LOG_INF("Advert LED blinking stopped\n");
}

void start_advert_led_blinking(void)
{
  if (is_adverting) {
    LOG_WRN("Couldn't start advert LED blinking - blinking already started\n");
    return;
  }
  is_adverting = true;
  advert_led_tid = k_thread_create(
      &advert_led_thread, advert_led_stack,
      K_THREAD_STACK_SIZEOF(advert_led_stack),
      (k_thread_entry_t)blink_advert_led,
      NULL, NULL, NULL,
      ADVERT_LED_THREAD_PRIORITY, 0, K_NO_WAIT);
}

void stop_advert_led_blinking(void)
{
  is_adverting = false;
}

void turn_on_connection_led(void) {
  dk_set_led(BT_CONNECTION_LED, true);
  LOG_INF("Connection LED turned on\n");
}

void turn_off_connection_led(void) {
  dk_set_led(BT_CONNECTION_LED, false);
  LOG_INF("Connection LED turned off\n");
}
