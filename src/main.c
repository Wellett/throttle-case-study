/** @file
 *  @brief Main file.
 *  @description Just contains some example code. Adapt it in the way you like.
 *  @note Test points used here can be used to develop unit tests
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "drivers/adc_driver/adc_driver.h"
#include "drivers/error_led/error_led.h"
#include "modules/sensors.h"

int main(int argc, char *argv[]) {
    adc_value_t value = 0;
    printf("[MAIN] Initialising\n");
    error_led_init();

    sensors_init();

    printf("[MAIN] Test point 5 deg\n");
    adc_read_set_output(ADC_CHANNEL0, 205, ADC_RET_OK);
    adc_read_set_output(ADC_CHANNEL1, 286, ADC_RET_OK);
    sensors_task();

    printf("[MAIN] Test point 5 deg\n");
    sensors_task();

    printf("[MAIN] Test point 7 deg\n");
    adc_read_set_output(ADC_CHANNEL0, 246, ADC_RET_OK);
    adc_read_set_output(ADC_CHANNEL1, 319, ADC_RET_OK);
    sensors_task();

    printf("[MAIN] Test point 30 deg\n");
    adc_read_set_output(ADC_CHANNEL0, 716, ADC_RET_OK);
    adc_read_set_output(ADC_CHANNEL1, 695, ADC_RET_OK);
    sensors_task();

    printf("[MAIN] Test point divergant sensors\n");
    adc_read_set_output(ADC_CHANNEL0, 409, ADC_RET_OK);
    sensors_task();

    printf("[MAIN] Test point divergant sensors\n");
    sensors_task();

    printf("[MAIN] Test point sensor failure\n");
    adc_read_set_output(ADC_CHANNEL0, 409, ADC_RET_NOK);
    sensors_task();
}



