#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "analogic_read.h"




void initiate_seed() {
    
    srand(2);  // Seed fixa para reprodutibilidade
}

#include <stdlib.h>

float random_angle_degrees() {
    int angle = (rand() % 36) + 10; // Gera número de 10 a 45
    if (rand() % 2 == 0) {
        return -angle;  // Negativo
    } else {
        return angle;   // Positivo
    }
}

