#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define DELAY_BUTTONS_US 150000

struct repeating_timer timer_contador;
const uint8_t I2C_SDA = 14;
const uint8_t I2C_SCL = 15;
ssd1306_t disp;
char buffer_segundos[4];
char buffer_b[4];

bool volatile button_a_nivel = false;
uint32_t volatile button_b_contador = 0;
int volatile contador = 10;

bool contador_decrescente_isr(struct repeating_timer *t)
{
    if (contador > 0)
    {
        contador--;
        sprintf(buffer_segundos, "%d", contador);
    }
}
void button_isr(uint gpio, uint32_t events)
{

    uint32_t tempo_instantaneo = time_us_32();
    static uint32_t tempo_anterior = 0;

    if (tempo_instantaneo - tempo_anterior > DELAY_BUTTONS_US)
    {
        if (gpio == BUTTON_A)
        {
            button_a_nivel = true;
        }
        if (gpio == BUTTON_B && contador != 0)
        {
            button_b_contador++;
            sprintf(buffer_b, "%d", button_b_contador);
        }
    }
    tempo_anterior = tempo_instantaneo;
}

void exibir_texto_sem_apagar(ssd1306_t *disp, char *words[], size_t word_count, uint x, uint y, uint scale)
{
    for (size_t i = 0; i < word_count; ++i)
    {
        ssd1306_draw_string(disp, x, y, scale, words[i]);
    }
}

int main()
{
    stdio_init_all();

    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_isr);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_isr);
    add_repeating_timer_ms(1000, contador_decrescente_isr, NULL, &timer_contador);
    sprintf(buffer_b, "%d", button_b_contador);

    while (true)
    {

        if (button_a_nivel)
        {
            contador = 10;
            button_a_nivel = false;
        }

        char *linha_segundos[] = {buffer_segundos};
        char *linha_b[] = {buffer_b};
        char *texto_1[] = {"Segundos:"};
        char *texto_2[] = {"Apertos de B:"};

        ssd1306_clear(&disp);
        exibir_texto_sem_apagar(&disp, texto_1, 1, 0, 24, 1);
        exibir_texto_sem_apagar(&disp, texto_2, 1, 0, 48, 1);
        exibir_texto_sem_apagar(&disp, linha_segundos, 1, 80, 24, 1);
        exibir_texto_sem_apagar(&disp, linha_b, 1, 80, 48, 1);
        ssd1306_show(&disp);
    }
}
