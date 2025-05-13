#ifndef DRAW_TABLE_H
#define DRAW_TABLE_H

#define NUM_PONTOS 15


// Stricture to represent a point in 2D space
typedef struct {
    int x;
    int y;
} Ponto;

// Variables
extern uint32_t cont_balls;
extern Ponto arvore[NUM_PONTOS];

// Function prototypes for drawing functions
void draw_tree (void);
void draw_tendencies(float tendencies);
void draw_line (void);
void draw_count(void);
void draw_table_complete (void);

#endif