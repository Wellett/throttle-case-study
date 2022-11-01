#pragma once
/** @file
 *  @brief header file for a sensor module
 *  @note in a larger system this might be part of a hal instead of in /modules
 */

//TODO use a build system that does not require aboslute paths...
#include "../drivers/adc_driver/adc_driver.h"
#include "moving_average.h"

/* @brief A simple double->double map
 */
typedef double (*sensor_map_f)(double);

/* @brief type to contain one sensor definition
 */
typedef struct angle_sensor {
    adc_channel_id_t adc_channel;
    sensor_map_f map_function;
    filter_t filter;
}angle_sensor_t;

/** @brief Initialises the angular sensors 
 */
void sensors_init(void);

/** @brief reads the angular sensors and combines the value
 */
void sensors_task(void);

