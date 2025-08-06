// geiger_counter.h
#ifndef GEIGER_COUNTER_H
#define GEIGER_COUNTER_H

#include <gpiod.h>

/** Initialize the Geiger counter (request GPIO events) */
void geiger_init(void);

/** Count pulses over the given interval in seconds and return the count */
int geiger_count_interval(int seconds);

/** Release GPIO resources */
void geiger_cleanup(void);

#endif // GEIGER_COUNTER_H
