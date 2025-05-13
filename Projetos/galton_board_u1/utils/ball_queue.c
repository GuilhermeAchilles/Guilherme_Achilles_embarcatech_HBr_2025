#include "ball_queue.h"
#include <stdbool.h> 

void init_queue(BallQueue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

bool enqueue(BallQueue *q, ball *b) {
    if (q->count >= MAX_BOLAS) return false;

    q->buffer[q->rear] = *b;
    q->rear = (q->rear + 1) % MAX_BOLAS;
    q->count++;
    return true;
}

bool dequeue(BallQueue *q, ball *b) {
    if (q->count == 0) return false;

    *b = q->buffer[q->front];
    q->front = (q->front + 1) % MAX_BOLAS;
    q->count--;
    return true;
}

ball* peek(BallQueue *q) {
    if (q->count == 0) return 0;
    return &q->buffer[q->front];
}
