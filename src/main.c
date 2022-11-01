/** @file
 *  @brief Main file.
 *  @description Just contains some example code. Adapt it in the way you like.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "drivers/adc_driver/adc_driver.h"
#include "drivers/error_led/error_led.h"
#include "modules/sensors.h"

int main(int argc, char *argv[]) {
  adc_value_t value = 0;
  angle_sensor_t sensor1;
  angle_sensor_t sensor0;

  error_led_init();
  //adc_init(ADC_CHANNEL1);
  init_angle_sensor(&sensor0, ADC_CHANNEL0, angle_sensor_1_characteristic_map);
  init_angle_sensor(&sensor1, ADC_CHANNEL1, angle_sensor_2_characteristic_map);

  adc_read_set_output(ADC_CHANNEL0, 205, ADC_RET_OK);
  adc_read_set_output(ADC_CHANNEL1, 286, ADC_RET_OK);
  adc_read(ADC_CHANNEL1, &value);

  printf("Angle sensor 0 angle: %.2f\n", read_angle_sensor(&sensor0));
  printf("Angle sensor 1 angle: %.2f\n", read_angle_sensor(&sensor1));

  adc_read_set_output(ADC_CHANNEL0, 716, ADC_RET_OK);
  printf("Angle sensor 0 angle: %.2f\n", read_angle_sensor(&sensor0));

  error_led_set(true);
}



