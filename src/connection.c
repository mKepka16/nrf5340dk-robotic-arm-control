#include "connection.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/conn.h>
#include "led.h"
#include "advert.h"

LOG_MODULE_REGISTER(Connection, LOG_LEVEL_INF);

static void recycled_cb(void)
{
  LOG_INF("Connection object available from previous conn. Disconnect is complete!\n");
  start_advertising();
}

static void on_connected(struct bt_conn *conn, uint8_t err)
{
  stop_advert_led_blinking();
  if (err)
  {
    LOG_ERR("Connection failed (err %u)\n", err);
    return;
  }

  turn_on_connection_led();
  LOG_INF("Connected\n");
}

static void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
  turn_off_connection_led();
  LOG_INF("Disconnected (reason %u)\n", reason);
}

struct bt_conn_cb connection_callbacks = {
    .connected = on_connected,
    .disconnected = on_disconnected,
    .recycled = recycled_cb,
};

void init_bt_connection(void) {
  bt_conn_cb_register(&connection_callbacks);
}