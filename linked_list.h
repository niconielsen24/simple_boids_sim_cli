#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdlib.h>
#include "quad_tree.h"

typedef struct _Node {
    XY elem;
    struct _Node* next;
} Node;

typedef struct _List {
    int size;
    Node* head; 
} List;

List empty_list();

List add(List l, XY e);

List destroy_list(List l);

List concat_list(List l1, List l2);

List tail(List l);

XY* list_to_arr(List l, XY* p);

#endif