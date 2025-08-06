// geiger_counter.c
#include "geiger_counter.h"
#include <signal.h>
#include <time.h>

#define GPIO_CHIP   "/dev/gpiochip4"
#define GPIO_LINE   17    // BCM17 for Geiger pulse input

static struct gpiod_chip *gc;
static struct gpiod_line *gl;
static volatile int pulse_count;

/** Set up the GPIO line for both-edge event detection */
void geiger_init(void) {
    gc = gpiod_chip_open(GPIO_CHIP);
    gl = gpiod_chip_get_line(gc, GPIO_LINE);
    gpiod_line_request_both_edges_events(gl, "PG_geiger");
}

/**
 * Waits for rising-edge events on the Geiger GPIO line
 * over 'seconds' seconds, counting each pulse.
 */
int geiger_count_interval(int seconds) {
    struct timespec timeout = {1, 0};
    struct gpiod_line_event event;
    time_t start = time(NULL);
    pulse_count = 0;
    while (time(NULL) - start < seconds) {
        if (gpiod_line_event_wait(gl, &timeout) > 0) {
            gpiod_line_event_read(gl, &event);
            if (event.event_type == GPIOD_LINE_EVENT_RISING_EDGE)
                pulse_count++;
        }
    }
    return pulse_count;
}

/** Release the GPIO line and close the chip */
void geiger_cleanup(void) {
    gpiod_line_release(gl);
    gpiod_chip_close(gc);
}
