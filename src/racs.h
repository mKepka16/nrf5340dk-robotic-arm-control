#ifndef RACS_H
#define RACS_H

#include <zephyr/bluetooth/uuid.h>

// RACS - Robot Arm Control Service

/** @brief RACS Service UUID. */
#define BT_UUID_RACS_VAL \
	BT_UUID_128_ENCODE(0x00000001, 0x46bf, 0x4a62, 0x9f7c, 0x54e268227875)
	
/** @brief Arm Position Characteristic UUID. */
#define BT_UUID_ARM_POS_CHAR_VAL \
	BT_UUID_128_ENCODE(0x00000002, 0x46bf, 0x4a62, 0x9f7c, 0x54e268227875)

#define BT_UUID_RACS BT_UUID_DECLARE_128(BT_UUID_RACS_VAL)
#define BT_UUID_ARM_POS_CHAR BT_UUID_DECLARE_128(BT_UUID_ARM_POS_CHAR_VAL)

#endif // RACS_H