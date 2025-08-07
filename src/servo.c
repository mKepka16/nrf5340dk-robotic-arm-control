#include "servo.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

LOG_MODULE_REGISTER(Servo, LOG_LEVEL_INF);

#define SERVOS_UPDATE_THREAD_PRIORITY 8
#define SERVOS_UPDATE_THREAD_STACK_SIZE 512

#define PWM_MID_PULSE_WIDTH 1450000
#define PWM_PULSE_RANGE_WIDTH 2000000

#define PWM_MIN_PULSE_WIDTH PWM_MID_PULSE_WIDTH - (PWM_PULSE_RANGE_WIDTH / 2)
#define PWM_MAX_PULSE_WIDTH PWM_MID_PULSE_WIDTH + (PWM_PULSE_RANGE_WIDTH / 2)

#define PWM_BIG_SERVO_0 DT_NODELABEL(big_servo_0)
#define PWM_BIG_SERVO_1 DT_NODELABEL(big_servo_1)
#define PWM_BIG_SERVO_2 DT_NODELABEL(big_servo_2)
#define PWM_SMALL_SERVO_0 DT_NODELABEL(small_servo_0)
#define PWM_SMALL_SERVO_1 DT_NODELABEL(small_servo_1)

#define SERVO_COUNT 5

#define PWM_PERIOD PWM_MSEC(20)

static const struct pwm_dt_spec big_servo_0 = PWM_DT_SPEC_GET(PWM_BIG_SERVO_0);
static const struct pwm_dt_spec big_servo_1 = PWM_DT_SPEC_GET(PWM_BIG_SERVO_1);
static const struct pwm_dt_spec big_servo_2 = PWM_DT_SPEC_GET(PWM_BIG_SERVO_2);
static const struct pwm_dt_spec small_servo_0 = PWM_DT_SPEC_GET(PWM_SMALL_SERVO_0);
static const struct pwm_dt_spec small_servo_1 = PWM_DT_SPEC_GET(PWM_SMALL_SERVO_1);
static const struct pwm_dt_spec *servos[] = {
  &big_servo_0,
  &big_servo_1,
  &big_servo_2,
  &small_servo_0,
  &small_servo_1
};

static uint8_t servo_data[5] = {128, 128, 128, 128, 128};

uint32_t servo_data_to_pulse(uint8_t position)
{
  return PWM_MIN_PULSE_WIDTH + (PWM_PULSE_RANGE_WIDTH * position / 255);
}

void servo_set_position(uint8_t servo_id, uint8_t position)
{
  if (servo_id < 5)
  {
    servo_data[servo_id] = position;
  }
}

void update_servos(void)
{
  int err;

  for (int i = 0; i < SERVO_COUNT; i++)
  {
    err = pwm_set_dt(servos[i], PWM_PERIOD, servo_data_to_pulse(servo_data[i]));
    if (err)
    {
      LOG_ERR("pwm_set_dt for servo %d returned %d", i, err);
    }
  }

  LOG_INF("%d %d %d %d %d\n", servo_data[0], servo_data[1], servo_data[2], servo_data[3], servo_data[4]);
}

void update_servos_thread(void)
{
  while (1)
  {
    update_servos();
    k_msleep(100);
  }
}

void init_servos(void)
{
  for (int i = 0; i < SERVO_COUNT; i++)
  {
    if (!pwm_is_ready_dt(servos[i]))
    {
      LOG_ERR("Error: PWM device %s is not ready", servos[i]->dev->name);
      return;
    }
  }
}


K_THREAD_DEFINE(servos_update_thread, SERVOS_UPDATE_THREAD_STACK_SIZE, update_servos_thread, NULL, NULL, NULL, SERVOS_UPDATE_THREAD_PRIORITY, 0, 0);