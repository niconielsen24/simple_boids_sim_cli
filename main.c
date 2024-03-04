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
    
    XY center = {0,0};
    int half_dim = trows()/2;
    AABB* bound = new_aabb(center, half_dim);
    QuadTree* tree = new_qtree(*bound);

    printf("%p\n",tree);

    for (int i = 0; i<10; i++) {
        if (insert_point(tree, boids[i].coordinate) != QTREE_NO_ERROR) {
            printf("Error while inserting point");
            return EXIT_FAILURE;
        }
    }
    
    for (int i = 0; i<4; i++) {
        printf("Point %i X:%i Y:%i \n",i,tree->points[i].x,tree->points[i].y);
    }

    for (int i = 4; i<8; i++) {
        printf("Point %i X:%i Y:%i \n",i,tree->southEast->points[i].x,tree->southEast->points[i].y);
    }

    printf("Tree nw %p\n",tree->northWest);
    printf("Tree ne %p\n",tree->northEast);
    printf("Tree sw %p\n",tree->southWest);
    printf("Tree se %p\n",tree->southEast);
    Query p = query_range(tree,bound);

    printf("%i\n",p.size);
    for (int i=0 ; i<p.size; i++) {
        printf("Point %i, X : %i, Y : %i\n",i,p.points[i].x,p.points[i].y);
    }

    destroy_tree(tree);
    destroy_aabb(bound);

    return EXIT_SUCCESS;
}