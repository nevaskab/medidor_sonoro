#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdint.h>

void buttons_init(void);
bool input_is_button_a_pressed(void);
bool input_is_button_b_pressed(void);
void irq_button(uint gpio, uint32_t events);

#endif 