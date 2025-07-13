#include <zephyr/kernel.h>
#include "led.h"
#include "advert.h"


int main(void)
{
  init_leds();

  while(1) {
    turn_on_connection_led();
    start_advert_led_blinking();
    k_msleep(5000);
    turn_off_connection_led();
    stop_advert_led_blinking();
    k_msleep(5000);
  }

  return 0;
}
