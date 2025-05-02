#include "hardware/adc.h"
#include "ler_temperatura.h"

void init_sensor (void){
    adc_init(); // Inicializa o ADC
    adc_set_temp_sensor_enabled(true) ;// Inicializa o sensor de temperatura
    adc_select_input(4); // Seleciona o canal ADC 4 (sensor de temperatura)
}

float read_tension_sensor (void){
    uint16_t value_sensor = adc_read();
    const float conversion_factor = 3.3f / (1 << 12); // Fator de conversão para tensão
    float voltage = value_sensor * conversion_factor; // Converte o valor lido para tensão
    return voltage; // Retorna a tensão lida
}