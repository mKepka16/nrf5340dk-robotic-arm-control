#include "racs.h"
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/logging/log.h>
#include "servo.h"

LOG_MODULE_REGISTER(Racs, LOG_LEVEL_DBG);

static ssize_t write_arm_pos(struct bt_conn *conn,
                             const struct bt_gatt_attr *attr,
                             const void *buf,
                             uint16_t len, uint16_t offset, uint8_t flags)
{
  LOG_DBG("Attribute write, handle: %u, conn: %p", attr->handle,
          (void *)conn);
  if (len != 2U)
  {
    LOG_DBG("Write led: Incorrect data length");
    return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
  }
  if (offset != 0)
  {
    LOG_DBG("Write led: Incorrect data offset");
    return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
  }
  // Read the received value
  uint8_t servo_id = ((uint8_t *)buf)[0];
  uint8_t servo_pos = ((uint8_t *)buf)[1];
  if (servo_id > 4) {
    LOG_DBG("Write led: Incorrect servo id");
    return BT_GATT_ERR(BT_ATT_ERR_VALUE_NOT_ALLOWED);
  }

  servo_set_position(servo_id, servo_pos);

  return len;
}

BT_GATT_SERVICE_DEFINE(
    rac_service,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_RACS),
    BT_GATT_CHARACTERISTIC(
        BT_UUID_ARM_POS_CHAR,
        BT_GATT_CHRC_WRITE,
        BT_GATT_PERM_WRITE,
        NULL,
        write_arm_pos,
        NULL));