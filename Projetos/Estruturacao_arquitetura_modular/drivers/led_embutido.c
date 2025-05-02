#include "pico/cyw43_arch.h"

int init_led_embutido (void){
    if (cyw43_arch_init()) {
        return -1;
    }
    return 0;
}

void led_embutido_control (bool state){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}