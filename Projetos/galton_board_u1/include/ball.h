#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    float position_initial[2];     
    float position_final[2];      
    float vel_x_y[2];               
    uint32_t time_ball; 
    float angle_impact; // Angulo de impacto     
    float state;   
    float tendencie;
    int detect_colision;
} ball;

// Declarações de funções
void create_ball(ball *b);
float return_tendencie(int adc_value);
void draw_ball(ball *b);
void change_state(ball *b);

#endif // BALL_H
