#include "gpio_ctrl.h"
#include <stdio.h>
#include <unistd.h>

static struct gpiod_chip  *chip_en, *chip_resn, *chip_cs;
static struct gpiod_line  *line_en, *line_resn, *line_cs;

void gpio_init() {
    // EN / RESN ???
    chip_en = gpiod_chip_open(EN_GPIO_CHIP);
    if (!chip_en) { perror("open EN chip"); return; }
    chip_resn = gpiod_chip_open(RESN_GPIO_CHIP);
    if (!chip_resn) { perror("open RESN chip"); return; }

    line_en   = gpiod_chip_get_line(chip_en,   EN_GPIO_LINE);
    line_resn = gpiod_chip_get_line(chip_resn, RESN_GPIO_LINE);
    if (!line_en  || !line_resn) {
        perror("get EN/RESN line"); return;
    }

    if (gpiod_line_request_output(line_en,   "en",   0) < 0 ||
        gpiod_line_request_output(line_resn, "resn", 0) < 0) {
        perror("request EN/RESN output"); return;
    }

    // CS ??????????
    chip_cs = gpiod_chip_open(CS_GPIO_CHIP);
    if (!chip_cs) { perror("open CS chip"); return; }

    line_cs = gpiod_chip_get_line(chip_cs, CS_GPIO_LINE);
    if (!line_cs) { perror("get CS line"); return; }

    if (gpiod_line_request_output(line_cs, "cs", 1) < 0) {
        perror("request CS output"); return;
    }
    // ???????
    gpiod_line_set_value(line_cs, 1);
}

void gpio_set_en(int value) {
    gpiod_line_set_value(line_en, value);
}

void gpio_set_resn(int value) {
    gpiod_line_set_value(line_resn, value);
}

void gpio_set_cs(int value) {
    gpiod_line_set_value(line_cs, value);
}

void gpio_cleanup() {
    // ?? EN/RESN/CS
    gpiod_line_release(line_en);
    gpiod_line_release(line_resn);
    gpiod_line_release(line_cs);
    gpiod_chip_close(chip_en);
    gpiod_chip_close(chip_resn);
    gpiod_chip_close(chip_cs);
}

