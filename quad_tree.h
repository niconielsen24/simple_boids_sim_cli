#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_

#include <stdbool.h>

#define QTREE_NO_ERROR                  0x00
#define QTREE_SUBDIVIDE_ALLOC_ERROR     0x01
#define QTREE_INSERT_ON_NULL_TREE_ERROR 0x02
#define QTREE_FAILED_INSERTION_ERROR    0x04
#define QTREE_NOT_CONTAINED             0x08

typedef struct _xy {
    int x;
    int y;
} XY;

typedef struct _AABB{
    XY center;
    int half_dimension;
} AABB;

typedef struct _QuadTree{
    AABB * bound;
    int count;

    XY * points;

    struct _QuadTree * northWest;
    struct _QuadTree * northEast;
    struct _QuadTree * southWest;
    struct _QuadTree * southEast;

} QuadTree;

XY * new_point(int x, int y);

AABB * new_aabb(XY center, int half_dimension);

QuadTree * new_qtree(AABB bound);

bool contains_point(AABB aabb, XY point);

bool aabb_intersection(AABB one, AABB two);

int subdivide(QuadTree * tree);

int insert_point(QuadTree * tree, XY point);

XY* destroy_point(XY* point);

AABB* destroy_aabb(AABB* aabb);

QuadTree* destroy_tree(QuadTree* tree);

#endif