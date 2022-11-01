/** @file
 *  @brief source file for a sensor module
 *  @note in a larger system this might be part of a hal instead of in /modules
 */

#include <stdio.h>
#include "sensors.h"

/* Constants */
#define ADC_MAX         1023
#define ADC_VOLTAGE     5.0
#define SENSOR1_SCALE   10.0
#define SENSOR1_OFFSET  -5.0
#define SENSOR2_SCALE   12.5
#define SENSOR2_OFFSET  -12.5 

/* Prototypes */
static double read_adc_voltage(adc_value_t adc, uint16_t adc_max, 
        double voltage_range);


void init_angle_sensor(angle_sensor_t *sensor, adc_channel_id_t adc_channel, 
        sensor_map_f map) {
    sensor->adc_channel = adc_channel;
    sensor->map_function = map;

    if (adc_init(adc_channel) != ADC_RET_OK){
        printf("Error: sensor not initialised successfully\n");
        //TODO trigger error system
    }
}

double read_angle_sensor(angle_sensor_t *sensor) {
    adc_value_t adc_value;
    if (adc_read(sensor->adc_channel, &adc_value) != ADC_RET_OK) {
        printf("Error: adc read unsuccessful\n");
        //TODO trigger error system
    }

    double voltage 
        = read_adc_voltage(adc_value, ADC_MAX, ADC_VOLTAGE);

    return sensor->map_function(voltage);
}

double angle_sensor_1_characteristic_map(double voltage) {
    return SENSOR1_SCALE*voltage + SENSOR1_OFFSET;
}

double angle_sensor_2_characteristic_map(double voltage) {
    return SENSOR2_SCALE*voltage + SENSOR2_OFFSET;
}

/* @brief converts from raw adc reading to voltage based on ADC parameters
 */
static double read_adc_voltage(adc_value_t adc, uint16_t adc_max, 
        double voltage_range) {
    if (adc > adc_max) {
        printf("Error ADC out of bounds\n");
        //TODO: trigger error system here
    }
    return adc*voltage_range/adc_max;
}
    



 
