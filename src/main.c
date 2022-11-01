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

  error_led_init();
  
  sensors_init();

  adc_read_set_output(ADC_CHANNEL0, 205, ADC_RET_OK);
  adc_read_set_output(ADC_CHANNEL1, 286, ADC_RET_OK);

  sensors_task();

  adc_read_set_output(ADC_CHANNEL0, 716, ADC_RET_OK);

  sensors_task();

  error_led_set(true);
}



