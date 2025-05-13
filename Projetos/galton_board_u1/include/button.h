#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include "pico/stdlib.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define DELAY_BUTTONS_US 150000

extern volatile bool button_a_nivel;

void init_buttons(void);
void init_button_interrupts(void);
void button_isr(uint gpio, uint32_t events);

#endif // BUTTONS_H
