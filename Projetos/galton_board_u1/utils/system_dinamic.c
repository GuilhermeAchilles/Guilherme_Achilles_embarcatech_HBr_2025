#include "ball.h"
#include "draw_table.h"
#include "random_number.h"
#include "write_display.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <hardware/timer.h>

void update_velocity(ball *b)
{

    float delta = (time_us_32() - b->time_ball) / 1e6f;
    float k;
    // Atualiza posição inicial
    if(b->position_initial[1] < b->position_final[1]){
        k = -2;
    }else{
        k = 2;
    }

    b->position_initial[0] = b->position_final[0];
    b->position_initial[1] = b->position_final[1] + k;

    float position_ball_y = b->position_final[1];
    float position_ball_x = b->position_final[0];

    float v_y = b->vel_x_y[1] = +b->vel_x_y[1] + 10 * delta;

    float speed = sqrtf(powf(b->vel_x_y[0], 2) + powf(v_y, 2)) * 0.4f;
    float vel_x = b->vel_x_y[0] = speed * sinf(b->angle_impact * 3.1415 / 180) + b->tendencie; // pequeno desvio lateral
    b->vel_x_y[1] = speed * cosf(b->angle_impact * 3.1415 / 180);                              // pequeno desvio vertical

    // Atualiza tempo
    b->time_ball = time_us_32();
}

void colision_wall(ball *b)
{

    b->vel_x_y[0] = -b->vel_x_y[0];
    b->time_ball = time_us_32();

    float position_ball_x = b->position_final[0];
    float position_ball_y = b->position_final[1];
    float k;

    if (fabs(position_ball_x - 104) < 3)
    {
         k = -1;
    }
    else if (fabs(position_ball_x - 24) < 3)
    {
        k = 1;
    }
    

    b->position_initial[0] = b->position_final[0]+k;
    b->position_initial[1] = b->position_final[1]+0.1;
}

// Calcula a nova posição com base no tempo decorrido
void calculate_pos(ball *b) {

    uint32_t now = time_us_32();
    float delta_time = (now - b->time_ball) / 1e6f;  // em segundos

    float angle = b->angle_impact = random_angle_degrees(); 
    float px = b->position_final[0] = (float)(b->position_initial[0] + b->vel_x_y[0] * delta_time );
    float py = b->position_final[1] = (float)(b->position_initial[1] + b->vel_x_y[1] * b->state * delta_time + delta_time*delta_time*10/2);
    printf("px: %f\n",delta_time);
    printf("px: %f\n",delta_time);

}


void colision(ball *b, float tendencie)
{

    float position_ball_x = b->position_final[0];
    float position_ball_y = b->position_final[1];

    if (fabs(position_ball_x - 24) < 3 || fabs(position_ball_x - 104) < 3)
    {
        colision_wall(b);
        return;
    }

    for (int i = 0; i < NUM_PONTOS; i++)
    {
        float point_x = arvore[i].x;
        float point_y = arvore[i].y;

        if (fabs(position_ball_x - point_x) <= 3.0f &&
            fabs(position_ball_y - point_y) <= 3.0f)
        {
            b->detect_colision = 1;
            b->tendencie = tendencie;
            change_state(b);
            update_velocity(b);
            return;
        }
    }
}

void check_velocity(ball *b)
{

    float delta = (time_us_32() - b->time_ball) / 1e6f;
    float velocity_y = b->vel_x_y[1] + 5 * b->state * delta;

    if (velocity_y < 1)
    {
        printf(" %f\n", velocity_y);
        b->detect_colision = 0;
        change_state(b);
        b->position_initial[0] = b->position_final[0];
        b->position_initial[1] = b->position_final[1];
        b->vel_x_y[1] = 0;
        b->time_ball = time_us_32();
    }
}

void update_display(ball *b)
{

    draw_count();
    draw_tree();
    draw_line();
    draw_ball(b);
}