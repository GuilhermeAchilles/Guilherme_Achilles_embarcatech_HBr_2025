#include <stdint.h>
#include <stdio.h>
#include "write_display.h"

float count_1 = 0;
float count_2 = 0;
float count_3 = 0;
float count_4 = 0;
float count_5 = 0;
float count_6 = 0;
float count_7 = 0;

void count_space(uint8_t pos_x, uint8_t pos_y)
{

    if (pos_y >= 63)
    {
        if (pos_x <= 44)
        {
            count_1++;
        }
        else if (pos_x <= 51)
        {
            count_2++;
        }
        else if (pos_x <= 59)
        {
            count_3++;
        }
        else if (pos_x <= 74)
        {
            count_4++;
        }
        else if (pos_x <= 81)
        {
            count_5++;
        }
        else if (pos_x <= 89)
        {
            count_6++;
        }
        else
        {
            count_7++;
        }
    }

}

void draw_graphics()
{
    float num_balls = count_1 + count_2 + count_3 + count_4 + count_5 + count_6 + count_7;
    if (num_balls != 0){

        draw_bar(35, 64 - (count_1 / num_balls) * 64, 8, 64);
        draw_bar(45, 64 - (count_2 / num_balls) * 64, 7, 64);
        draw_bar(55, 64 - (count_3 / num_balls) * 64, 7, 64);
        draw_bar(65, 64 - (count_4 / num_balls) * 64, 7, 64);
        draw_bar(75, 64 - (count_5 / num_balls) * 64, 7, 64);
        draw_bar(85, 64 - (count_6 / num_balls) * 64, 7, 64);
        draw_bar(95, 64 - (count_7 / num_balls) * 64, 7, 64);
    }
 }


