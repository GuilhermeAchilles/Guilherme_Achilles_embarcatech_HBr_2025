#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/timer.h>
#include "draw_table.h"
#include "write_display.h"
#include "ball.h"
#include "random_number.h"
#include "system_dinamic.h"
#include <math.h>
#include "ball_queue.h"
#include "button.h"
#include "draw_graphic.h"
#include "analogic_read.h"

BallQueue fila;
absolute_time_t ultimo_spawn;
struct repeating_timer timer_contador, timer_adc;

volatile bool atualizar_display = false;

// === Função chamada periodicamente pelo timer ===

bool update_balls_timer_callback(struct repeating_timer *t)
{

    clear_display();

    float tendencie = return_tendencie(read_adc());


    for (int i = 0, idx = fila.front; i < fila.count;)
    {
        ball *b = &fila.buffer[idx];
        printf("b->state1: %f\n",b->state);
        colision(b, tendencie);
        calculate_pos(b);
        
    
        if (b->state == -1)
        {
            check_velocity(b);
        }
        update_display(b);
        count_space((uint8_t)b->position_final[0], (uint8_t)b->position_final[1]);

        if (b->position_final[1] > 64)
        {
            ball lixo;
            dequeue(&fila, &lixo);
        }

        i++;
        idx = (idx + 1) % MAX_BOLAS;
    }
    draw_tendencies(tendencie);
    atualizar_display = true;
    return true; // Mantém o timer ativo
}

int main()
{
    stdio_init_all();
    init_display();
    init_buttons();
    init_adc();
    initiate_seed();
    init_queue(&fila);
    ultimo_spawn = get_absolute_time();
    init_button_interrupts();

    // Inicia o timer com intervalo de 100ms
    add_repeating_timer_ms(100, update_balls_timer_callback, NULL, &timer_contador);

    bool timer_reativado = true;

    while (1)
    {
        // Criação periódica de novas bolas
        if (absolute_time_diff_us(ultimo_spawn, get_absolute_time()) > 90000)
        {
            ball nova_bola;
            create_ball(&nova_bola);

            if (fila.count < MAX_BOLAS)
            {
                enqueue(&fila, &nova_bola);
                cont_balls++;
            }

            ultimo_spawn = get_absolute_time();
        }

        // Modo gráfico enquanto botão A está pressionado
        if (button_a_nivel)
        {
            cancel_repeating_timer(&timer_contador);
            timer_reativado = false;

            while (button_a_nivel)
            {
                clear_display();
                draw_graphics((float)cont_balls);
                show_display();
                sleep_ms(100);
            }
        }

        // Reinicia o timer se não estiver ativo
        if (!timer_reativado)
        {
            add_repeating_timer_ms(100, update_balls_timer_callback, NULL, &timer_contador);
            timer_reativado = true;
        }

        // Atualiza a tela apenas se sinalizado pela interrupção
        if (atualizar_display)
        {
            show_display();
            atualizar_display = false;
        }

        tight_loop_contents(); // Uso eficiente da CPU
    }
}
