#ifndef GPIO_CTRL_H
#define GPIO_CTRL_H

#include <gpiod.h>

// EN ? RESN ??? GPIO chip ? line
#define EN_GPIO_CHIP    "/dev/gpiochip0"
#define RESN_GPIO_CHIP  "/dev/gpiochip0"
#define EN_GPIO_LINE    22      // BCM22
#define RESN_GPIO_LINE  27      // BCM27

// ???CS ??? GPIO chip ? line
#define CS_GPIO_CHIP    "/dev/gpiochip0"
#define CS_GPIO_LINE    25      // BCM25

void gpio_init(void);
void gpio_set_en(int value);
void gpio_set_resn(int value);

// ????? CS
void gpio_set_cs(int value);

void gpio_cleanup(void);

#endif // GPIO_CTRL_H
