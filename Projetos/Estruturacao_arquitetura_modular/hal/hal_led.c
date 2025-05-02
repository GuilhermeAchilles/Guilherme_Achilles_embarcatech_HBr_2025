#include "include/hal_led.h"


void led_toogle(void) {
    static bool led_embutido_state = false;
    led_embutido_state = !led_embutido_state;
    led_embutido_control(led_embutido_state);
    sleep_ms(500);
}
