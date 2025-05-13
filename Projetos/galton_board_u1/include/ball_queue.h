#ifndef BALL_QUEUE_H
#define BALL_QUEUE_H

#include "ball.h"
#include <stdbool.h> 

#define MAX_BOLAS 1000
 
typedef struct {
    ball buffer[MAX_BOLAS];
    int front;
    int rear;
    int count;
} BallQueue;

void init_queue(BallQueue *q);
bool enqueue(BallQueue *q, ball *b);
bool dequeue(BallQueue *q, ball *b);
ball* peek(BallQueue *q);  // Opcional: acessar a bola da frente sem remover

#endif
