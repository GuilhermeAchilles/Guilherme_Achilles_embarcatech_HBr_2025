#include <hardware/adc.h>

void init_adc(void){
    adc_init();
    adc_gpio_init(27);
    adc_gpio_init(28);
}

int read_adc(void){
    adc_select_input(1);
    int sum = 0;
    for (uint8_t i = 0; i<100 ;i++){
        sum += adc_read();
    }
    
    return sum/100;
}

int read_adc_2(void){
    adc_select_input(1);
    int sum = 0;
    for (uint8_t i = 0; i<100 ;i++){
        sum += adc_read();
    }
    
    return sum/100;
}

