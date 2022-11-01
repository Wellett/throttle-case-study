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
#define FILTER_LEN      10

/* Function Declarations */
static double read_adc_voltage(adc_value_t adc, uint16_t adc_max, 
        double voltage_range);
static void angle_sensor_update(angle_sensor_t *sensor);
static void init_angle_sensor(angle_sensor_t *sensor, 
        adc_channel_id_t adc_channel, sensor_map_f map);
static double read_angle_sensor(angle_sensor_t *sensor);
static double angle_sensor_1_characteristic_map(double voltage);
static double angle_sensor_2_characteristic_map(double voltage);

/* Sensors */
static angle_sensor_t sensor0;
static angle_sensor_t sensor1;

/* Public function defintions */

void sensors_init(void) {
    init_angle_sensor(&sensor0, ADC_CHANNEL0, 
            angle_sensor_1_characteristic_map);
    init_angle_sensor(&sensor1, ADC_CHANNEL1, 
            angle_sensor_2_characteristic_map);
}

void sensors_task(void) {
    angle_sensor_update(&sensor0);
    angle_sensor_update(&sensor1);
}

/* Private function defintions */

/** @brief Initialises a virutal angle sensor object
 *  @param[in] sensor the sensor object to initialise
 *  @param[in] adc_channel the adc channel used by the sensor
 *  @param[in] map double->double map for adc output to sensor reading 
 *      characteristic
 *  @note The adc is also initialised, this should not be initialised prior
 */
static void init_angle_sensor(angle_sensor_t *sensor, adc_channel_id_t 
        adc_channel, sensor_map_f map) {
    sensor->adc_channel = adc_channel;
    sensor->map_function = map;

    double sensor_buffer[FILTER_LEN];

    moving_average_filter_init(&(sensor->filter), sensor_buffer, FILTER_LEN);

    if (adc_init(adc_channel) != ADC_RET_OK){
        printf("Error: sensor not initialised successfully\n");
        //TODO trigger error system
    }
}

/** @brief updates a virtual sensor and feeds the filter
 *  @param[in] sensor the virtual sensor to update
 */
static void angle_sensor_update(angle_sensor_t *sensor) {
    double new_value = read_angle_sensor(sensor);
    printf("sensor_read %.2f\n", new_value);
    sensor->filter.feed(&(sensor->filter), new_value);
    double filtered_value = sensor->filter.read(&sensor->filter);
    printf("sensor filter read: %f\n", filtered_value);
}


/** @brief Reads the value of the virtual sensor
 *  @param[in] sensor the virtual sensor to read
 *  @returns the angle read
 */
static double read_angle_sensor(angle_sensor_t *sensor) {
    adc_value_t adc_value;
    if (adc_read(sensor->adc_channel, &adc_value) != ADC_RET_OK) {
        printf("Error: adc read unsuccessful\n");
        //TODO trigger error system
    }

    double voltage 
        = read_adc_voltage(adc_value, ADC_MAX, ADC_VOLTAGE);

    return sensor->map_function(voltage);
}

/** @brief sensor characteristic for sensor1
 *  @param[in] voltage
 *  @returns angle in degrees
 *  @Note This is labelled "1" to correspond to eqn 1 in the readme
 */
static double angle_sensor_1_characteristic_map(double voltage) {
    return SENSOR1_SCALE*voltage + SENSOR1_OFFSET;
}

/** @brief sensor characteristic for sensor2
 *  @param[in] voltage
 *  @returns angle in degrees
 *  @Note This is labelled "2" to correspond to eqn 2 in the readme
 */
static double angle_sensor_2_characteristic_map(double voltage) {
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
    



 
