#include "pico/stdlib.h"
#include "include/hal_led.h"
#include "include/led_embutido.h"

int main() {

    stdio_init_all();

    if (init_led_embutido() != 0) {
        return -1;
    }

    while (true) {
        led_toogle();
    }
    return 0;
}