#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

const uint8_t vRy = 27;
const uint8_t vRx = 26;
int volatile valor_x = 0;
int volatile valor_y = 0;

const uint8_t I2C_SDA = 14;
const uint8_t I2C_SCL = 15;
ssd1306_t disp;

#define JANELA 50
int volatile buffer_x[JANELA] = {0}, buffer_y[JANELA] = {0};
int volatile indice_x = 0, indice_y = 0;
int volatile soma_x = 0, soma_y = 0;
int volatile media_x = 0, media_y = 0;

struct repeating_timer timer_joystick_x, timer_joystick_y;

bool ler_joystick_x(struct repeating_timer *t)
{
    adc_select_input(1);
    valor_x = adc_read();

    soma_x = soma_x - buffer_x[indice_x] + valor_x; // Remove o valor mais antigo da soma
    buffer_x[indice_x] = valor_x;                   // Adiciona o novo valor ao buffer
    indice_x = (indice_x + 1) % JANELA;             // Atualiza o índice circular
    media_x = soma_x / JANELA;                      // Calcula a média

    return true;
}
bool ler_joystick_y(struct repeating_timer *t)
{
    adc_select_input(0);
    valor_y = adc_read();

    soma_y = soma_y - buffer_y[indice_y] + valor_y; // Remove o valor mais antigo da soma
    buffer_y[indice_y] = valor_y;                   // Adiciona o novo valor ao buffer
    indice_y = (indice_y + 1) % JANELA;             // Atualiza o índice circular
    media_y = soma_y / JANELA;                      // Calcula a média

    return true;
}

void exibir_texto_sem_apagar(ssd1306_t *disp, char *words[], size_t word_count, uint x, uint y, uint scale)
{
    ssd1306_draw_string(disp, x, y, scale, words[0]);
}

int main()
{
    stdio_init_all();
    adc_init();
    adc_gpio_init(vRx);
    adc_gpio_init(vRy);

    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    add_repeating_timer_ms(40, ler_joystick_x, NULL, &timer_joystick_x);
    add_repeating_timer_ms(40, ler_joystick_y, NULL, &timer_joystick_y);
    sleep_ms(2000);

    char buffer_x[5];
    char buffer_y[5];
    int media_anterior_x = 0;
    int media_anterior_y = 0;

    while (true)
    {

        sprintf(buffer_x, "%d", media_x);
        sprintf(buffer_y, "%d", media_y);

        char *text_1[] = {"Joystick X: "};
        char *text_2[] = {"Joystick Y: "};
        char *text_3[] = {buffer_x};
        char *text_4[] = {buffer_y};

        if (media_anterior_x != media_x || media_anterior_y != media_y)
        {
            ssd1306_clear(&disp);
            exibir_texto_sem_apagar(&disp, &text_2, 1, 0, 36, 1);
            exibir_texto_sem_apagar(&disp, &text_4, 1, 72, 36, 1);
            exibir_texto_sem_apagar(&disp, &text_1, 1, 0, 18, 1);
            exibir_texto_sem_apagar(&disp, &text_3, 1, 72, 18, 1);
            ssd1306_show(&disp);

            media_anterior_x = media_x;
            media_anterior_y = media_y;
        }
        sleep_ms(20);
    }
}
