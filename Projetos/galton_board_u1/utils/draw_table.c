#include "write_display.h"
#include <stdio.h>
#include "draw_graphic.h"

#define NUM_PONTOS 15

uint32_t cont_balls = 0;

typedef struct {
    int x;
    int y;
} Ponto;

Ponto arvore[NUM_PONTOS] = {
    {64, 10},
    {57, 20}, {72, 20},
    {49, 30}, {64, 30}, {79, 30},
    {42, 40}, {57, 40}, {72, 40}, {87, 40},
  {34,50}, {49, 50}, {64, 50}, {79, 50}, {94,50}
};


void draw_tree (void){
    for (int i=0; i<NUM_PONTOS;i++){
        write_char('o',1,arvore[i].x,arvore[i].y,1);
    }
}

void draw_line (void){

    uint8_t passo = 15;

    write_line(24,0,24,64);
    write_line(104,0,104,64);

    for (int i = 0 ; i<2;i++){
        write_line(51+i*2*passo,59,51+i*2*passo,64);
    }
    for (int i = 0 ; i<4;i++){
        write_line(44+i*passo,59,44+i*passo,64);
    }
}

void draw_count (void){
    char buffer[20];
    // Soma todos os contadores e converte para int
    int cont_balls_ex = (int)(count_1+count_2+count_3+count_4+count_5+count_6+count_7);
    // Usa %d para formatar inteiros
    sprintf(buffer, "%d", cont_balls_ex);
    char *text[] = {buffer};
    write_string(text, 3, 20, 1);
}

void draw_tendencies(float tendencies){
    char *right[] = {"--->"};
    char *left[] = {"<---"};
    char *mid[] = {"-|-"};
    
    if(tendencies > 1){
        write_string(right,105,20,1);
        return;
    }else if(tendencies < -1){
        write_string(left,105,20,1);
        return;
    }else{
        write_string(mid,110,20,1);
        return;
    }
}

void draw_table_complete (void){
    draw_tree();
    draw_line();
    draw_count();
}