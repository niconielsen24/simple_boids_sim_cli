#include <stdio.h>
#include <stdlib.h>
#include "quad_tree.h"
#include "rogueutil.h"

#define RANGE 3

typedef struct _Boid{
    XY coordinate;
    XY direction;
} Boid;

int main(){
    cls();

    Boid boids[10];
    for (int i = 0; i < 10; i++)
    {
        boids[i].coordinate.x = i;
        boids[i].coordinate.y = i;
    }
    
    int height = trows()-1;
    int width = tcols()-1;
    char matrix[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = ' ';
            for (int k = 0; k < 10; k++)
            {
                if (i == boids[k].coordinate.y && j == boids[k].coordinate.x)
                {
                    matrix[i][j] = '*';
                }
            }
        }
        matrix[i][width-1] = '\n';
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           printf("%c",matrix[i][j]);
        }
    }

    msleep(5000);

    cls();
    return EXIT_SUCCESS;
}