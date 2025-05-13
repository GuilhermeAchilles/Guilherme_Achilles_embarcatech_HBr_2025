#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hardware/timer.h"
#include "write_display.h"
#include "random_number.h"

typedef struct {
    float position_initial[2];     
    float position_final[2];      
    float vel_x_y[2];               
    uint32_t time_ball; 
    float angle_impact;         
    float state;
    float tendencie;
    int detect_colision;
} ball;

float return_tendencie(int adc_value) {
    if (adc_value >= 1900 && adc_value <= 2200) {
        return 0.0f;
    } else if (adc_value > 2200 && adc_value <= 4078) {
        // Mapeia de 1 a 5 proporcionalmente
        float k = ((float)(adc_value - 2200) / (4078 - 2200)) * 4.0f + 1.0f;
        return k;
    } else if (adc_value >= 0 && adc_value < 1900) {
        // Mapeia de -5 a 0 proporcionalmente
        float k = -5.0f + ((float)adc_value / 1900.0f) * 5.0f;
        return k;
    }

    // Valor fora do intervalo esperado
    return 0.0f;
}


// Inicializa a bola
void create_ball(ball *b) {
    b->position_initial[0] = 64;
    b->position_initial[1] = 0;
    b->vel_x_y[0] = 0;
    b->vel_x_y[1] = 2;
    b->time_ball = time_us_32(); // salva o tempo atual
    b->state = 1;
    b->tendencie = 0;
    b->detect_colision = 0;
}

void draw_ball(ball *b) {
    write_char('.', 1,  (uint8_t)b->position_final[0],(uint8_t)b->position_final[1], 1);
}

void change_state(ball *b){
    b->state = -1*b->state;
}