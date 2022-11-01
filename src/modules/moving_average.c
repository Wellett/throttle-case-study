/** @file 
 *  @brief source file for a movig average filter (digital low pass)
 */

#include "moving_average.h"
#include <stdio.h>

static void moving_average_filter_feed(filter_t *filter, double new_value);
static double moving_average_filter_read(filter_t *filter);

void moving_average_filter_init(filter_t *filter, double* data, uint8_t length) {
    filter->feed = moving_average_filter_feed;
    filter->read = moving_average_filter_read;
    filter->count = 0;
    filter->position = 0;
    filter->length = length;
    filter->values = data;
    filter->accumulator = 0;
}

/** @brief implements filter feed for moving average
 */
static void moving_average_filter_feed(filter_t *filter, double new_value) {
    if (filter->count < filter->length) {
        filter->count++;
    }
    //update accumulator
    filter->accumulator -= filter->values[filter->position];
    filter->accumulator += new_value;

    //update position
    filter->values[filter->position] = new_value;
    filter->position = (filter->position + 1)%filter->length;
}

/** @brief implements filter read for moving average
 */
static double moving_average_filter_read(filter_t *filter) {

    return (filter->accumulator / filter->count);
}
