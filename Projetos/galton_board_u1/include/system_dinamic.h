#ifndef SYSTEM_DINAMIC_H
#define SYSTEM_DINAMIC_H



void update_velocity(ball *b);
void calculate_pos(ball *b);
void colision(ball *b, float tendencie);
void colision_wall (ball *b);
void update_display (ball *b);
void check_velocity(ball *b);


#endif 