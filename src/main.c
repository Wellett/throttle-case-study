#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "drivers/adc_driver/adc_driver.h"
#include "drivers/error_led/error_led.h"

int main(int argc, char *argv[]) {
  adc_value_t value = 0;
  adc_channel_id_t channel_id = ADC_CHANNEL0;

  error_led_init();
  adc_init(ADC_CHANNEL1);

  error_led_set(true);
  error_led_set(false);

  adc_read_set_output(ADC_CHANNEL1, 120, ADC_RET_NOK);

  adc_read(ADC_CHANNEL1, &value);
}
