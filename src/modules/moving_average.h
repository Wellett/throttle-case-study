/** @file
 *  @brief header file for a moving average filter (digital low pass)
 *  Note: if more filter types were introduced the filter type would be 
 *  abstracted as an interface, this would of course work more nicely in a 
 *  language with inheritance.
 */

#include <stdint.h>


/** @brief struct to contain one filter instance */
typedef struct filter filter_t;

/** @brief function type for filter feed
 *  called periodically to update the filter with each new sample
 *  @param[in] filter the filter to feed
 *  @param[in] new the new falue
 */
typedef void (*filter_feed_f)(filter_t*, double);

/** @brief function type for filter read
 *  @param[in] filter the filter to read
 *  @returns the current filter value
 */
typedef double (*filter_read_f)(filter_t*);

/** @brief struct to contain one filter instance */
struct filter {
    filter_feed_f feed;
    filter_read_f read;
    uint8_t count;
    uint8_t position;
    uint8_t length;
    double *values;
    double accumulator;
};
 

/** @brief Initialises the filter struct as a moving average filter
 *  @param[in] filter the filter to initialise
 *  @param[in] data the data buffer, this MUST be initialised first
 *  @param[in] length the desired filter length (window width)
 */
void moving_average_filter_init(filter_t *filter, double* data, uint8_t length);
