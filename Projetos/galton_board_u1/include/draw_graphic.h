// ball_stats.h

#ifndef DRAW_GRAPHIC_H
#define DRAW_GRAPHIC_H

#include <stdint.h>
#include "write_display.h"

// Contadores para cada região
extern float count_1;
extern float count_2;
extern float count_3;
extern float count_4;
extern float count_5;
extern float count_6;
extern float count_7;


// Função para contar a posição onde a bola caiu
void count_space(uint8_t pos_x, uint8_t pos_y);

// Função para desenhar os gráficos (barras) com base nos contadores
void draw_graphics(float num_balls);

#endif // BALL_STATS_H
