#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "inc/ssd1306.h"

volatile uint16_t adc_result = 0;
const uint8_t I2C_SDA = 14;
const uint8_t I2C_SCL = 15;
ssd1306_t disp;

void exibir_texto_sem_apagar(ssd1306_t *disp, char *words[], size_t word_count, uint x, uint y, uint scale)
{
    ssd1306_draw_string(disp, x, y, scale, words[0]);
}

float adc_to_temperature(uint16_t adc_value) {
    const float conversion_factor = 3.3f / (1 << 12); 
    float voltage = adc_value * conversion_factor;     
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;  
    return temperature;
}

void adc_isr() {
    adc_result = adc_fifo_get();      // ✅ Lê valor do ADC da FIFO
    // FIFO vai limpar automaticamente ao ler
}

int main() {
    stdio_init_all();

    adc_init();                               // Inicializa ADC
    adc_set_temp_sensor_enabled(true);        // Ativa sensor interno
    adc_select_input(4);                      // Canal 4 = sensor de temperatura

    adc_fifo_setup(
        true,    // Enable FIFO
        true,    // Enable IRQ on FIFO threshold
        1,       // IRQ a cada amostra
        false,
        false
    );

    adc_fifo_drain();                         // Limpa FIFO

    adc_irq_set_enabled(true);                // Habilita IRQ do ADC
    irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_isr);
    irq_set_enabled(ADC_IRQ_FIFO, true);

    adc_run(true);                            // Começa a conversão

    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    char buffer_temperature[3];
    float sum = 0, buffer_avg [20] = {0}, avg = 0;
    int index = 0;
    char *text_1[] = {"Temperatura CPU: "};
    char *text_2[] = {"ºC"}; 

    while (1) {

        float temperature = adc_to_temperature(adc_result);
        sprintf(buffer_temperature, "%.2f", temperature);

        sum = sum - buffer_avg[index] + temperature;
        buffer_avg[index] = temperature;
        index = (index + 1) % 20; // Circular buffer
        avg = sum / 20.0f;

        sprintf(buffer_temperature, "%.2f", avg);

        if(index == 19) {
            sprintf(buffer_temperature, "%.2f", avg);
            char *text_3[] = {buffer_temperature};
            ssd1306_clear(&disp);
            exibir_texto_sem_apagar(&disp, text_1, 1, 20, 16, 1);
            exibir_texto_sem_apagar(&disp, text_2, 1, 70, 32, 2);
            exibir_texto_sem_apagar(&disp, text_3, 1, 25, 32, 2);
            ssd1306_show(&disp);
        }
        sleep_ms(50);
    }
}
