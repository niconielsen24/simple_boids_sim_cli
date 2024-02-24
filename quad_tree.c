#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "quad_tree.h"

XY* new_point(int x, int y){
    XY* point = malloc(sizeof(XY));
    point->x = x;
    point->y = y;
    return point;
}

AABB* new_aabb(XY cntr, int half_dim){
    AABB* box = malloc(sizeof(AABB));
    box->center = cntr;
    box->half_dimension = half_dim;
    return box;
}

QuadTree* new_qtree(AABB box){
    QuadTree* tree = malloc(sizeof(QuadTree));
    if (tree == NULL){
        fprintf(stderr,"Failed to allocate tree\n");
        return NULL;
    }
    
    tree->bound = malloc(sizeof(AABB));
    if (tree->bound == NULL){
        fprintf(stderr,"Failed to allocate tree bound\n");
        return NULL;
    }
    
    *(tree->bound) = box;
    tree->points = malloc(4 * sizeof(XY));
    tree->count = 0;
    tree->northWest = NULL;
    tree->northEast = NULL;
    tree->southWest = NULL;
    tree->southEast = NULL;
    return tree;
}

bool contains_point(AABB aabb, XY point){
    return
    (point.x <= aabb.center.x + aabb.half_dimension) &&
    (point.x >= aabb.center.x - aabb.half_dimension) &&
    (point.y <= aabb.center.y + aabb.half_dimension) &&
    (point.y >= aabb.center.y - aabb.half_dimension)
    ;
}

bool aabb_intersection(AABB one, AABB two) {
    int minX1 = one.center.x - one.half_dimension;
    int minY1 = one.center.y - one.half_dimension;
    int maxX1 = one.center.x + one.half_dimension;
    int maxY1 = one.center.y + one.half_dimension;

    int minX2 = two.center.x - two.half_dimension;
    int minY2 = two.center.y - two.half_dimension;
    int maxX2 = two.center.x + two.half_dimension;
    int maxY2 = two.center.y + two.half_dimension;

    if (maxX1 < minX2 || minX1 > maxX2 || maxY1 < minY2 || minY1 > maxY2) {
        return false;
    } else {
        return true;
    }
}

int subdivide(QuadTree * tree){
    XY* centerNw = new_point(tree->bound->center.x - (tree->bound->half_dimension / 2), tree->bound->center.y + (tree->bound->half_dimension / 2));
    XY* centerNe = new_point(tree->bound->center.x + (tree->bound->half_dimension / 2), tree->bound->center.y + (tree->bound->half_dimension / 2));
    XY* centerSw = new_point(tree->bound->center.x - (tree->bound->half_dimension / 2), tree->bound->center.y - (tree->bound->half_dimension / 2));
    XY* centerSe = new_point(tree->bound->center.x + (tree->bound->half_dimension / 2), tree->bound->center.y - (tree->bound->half_dimension / 2));

    AABB* boundNw = new_aabb(*centerNw, tree->bound->half_dimension / 2);
    AABB* boundNe = new_aabb(*centerNe, tree->bound->half_dimension / 2);
    AABB* boundSw = new_aabb(*centerSw, tree->bound->half_dimension / 2);
    AABB* boundSe = new_aabb(*centerSe, tree->bound->half_dimension / 2);

    tree->northWest = new_qtree(*boundNw);
    if (tree->northWest == NULL) return QTREE_SUBDIVIDE_ALLOC_ERROR;
    
    tree->northEast = new_qtree(*boundNe);
    if (tree->northEast == NULL) return QTREE_SUBDIVIDE_ALLOC_ERROR;
    
    tree->southWest = new_qtree(*boundSw);
    if (tree->southWest == NULL) return QTREE_SUBDIVIDE_ALLOC_ERROR;
    
    tree->southEast = new_qtree(*boundSe);
    if (tree->southEast == NULL) return QTREE_SUBDIVIDE_ALLOC_ERROR;
    return QTREE_NO_ERROR;
}

int insert_point(QuadTree * tree, XY point){

    if (tree == NULL) return QTREE_INSERT_ON_NULL_TREE_ERROR;

    if (!contains_point(*(tree->bound),point)) return QTREE_NOT_CONTAINED;
    
    if (tree->northWest == NULL &&   tree->count < 4){
        tree->points[tree->count++] = point;
        return QTREE_NO_ERROR;
    }
    
    int err;
    if (tree->northWest == NULL) err = subdivide(tree);
    if (err == QTREE_SUBDIVIDE_ALLOC_ERROR) return err;

    if (insert_point(tree->northWest,point) == QTREE_NO_ERROR) return QTREE_NO_ERROR;
    if (insert_point(tree->northEast,point) == QTREE_NO_ERROR) return QTREE_NO_ERROR;
    if (insert_point(tree->southWest,point) == QTREE_NO_ERROR) return QTREE_NO_ERROR;
    if (insert_point(tree->southEast,point) == QTREE_NO_ERROR) return QTREE_NO_ERROR;

    return QTREE_FAILED_INSERTION_ERROR;
}

XY* destroy_point(XY* point){
    free(point);
    return NULL;
}

AABB* destroy_aabb(AABB* aabb){
    free(aabb);
    return NULL;
}

QuadTree* destroy_tree(QuadTree* tree){
    if (tree->northWest != NULL)
    {
        destroy_tree(tree->northWest);
        destroy_tree(tree->northEast);
        destroy_tree(tree->southWest);
        destroy_tree(tree->southEast);
    }

    destroy_aabb(tree->bound);
    free(tree->points);
    free(tree);
    return NULL;
}