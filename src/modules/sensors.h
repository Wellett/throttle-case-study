/** @file
 *  @brief header file for a sensor module
 *  @note in a larger system this might be part of a hal instead of in /modules
 */

//TODO use a build system that does not require aboslute paths...
#include "../drivers/adc_driver/adc_driver.h"

/* @brief A simple double->double function type
 */
typedef double (*sensor_map_f)(double);

/* @brief type to contain one sensor definition
 */
typedef struct angle_sensor {
    adc_channel_id_t adc_channel;
    sensor_map_f map_function;
}angle_sensor_t;

/** @brief Initialises a virutal angle sensor object
 *  @param[in] sensor the sensor object to initialise
 *  @param[in] adc_channel the adc channel used by the sensor
 *  @param[in] map double->double map for adc output to sensor reading 
 *      characteristic
 *  @note The adc is also initialised, this should not be initialised prior
 */
void init_angle_sensor(angle_sensor_t *sensor, adc_channel_id_t adc_channel, 
        sensor_map_f map);

/** @brief Reads the value of the virtual sensor
 *  @param[in] sensor the virtual sensor to read
 *  @returns the angle read
 */
double read_angle_sensor(angle_sensor_t *sensor);


/** @brief sensor characteristic for sensor1
 *  @param[in] voltage
 *  @returns angle in degrees
 *  @Note This is labelled "1" to correspond to eqn 1 in the readme
 */
double angle_sensor_1_characteristic_map(double voltage);

/** @brief sensor characteristic for sensor2
 *  @param[in] voltage
 *  @returns angle in degrees
 *  @Note This is labelled "2" to correspond to eqn 2 in the readme
 */
double angle_sensor_2_characteristic_map(double voltage);
