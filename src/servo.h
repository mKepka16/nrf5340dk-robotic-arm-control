#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>

void servo_set_position(uint8_t servo_id, uint8_t position);

void init_servos(void);

#endif // SERVO_H