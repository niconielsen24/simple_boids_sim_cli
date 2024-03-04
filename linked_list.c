#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include "linked_list.h"
#include "quad_tree.h"

List empty_list(){
    List l;
    l.size = 0;
    l.head = NULL;
    return l;
}

List add(List l, XY e){
    l.size +=1;
    Node* n = malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "Failed to allocate node");
        return l;
    }
    n->elem = e;
    n->next = l.head;
    l.head = n;
    return l;
}

List concat_list(List l1, List l2){
    
    if (l1.head == NULL) {
        l1.head = l2.head;
        l1.size=l2.size;
        return l1;
    } else if (l2.head == NULL) {
        return l1;
    }

    Node* n = l1.head;

    while (n->next != NULL) {
        n = n->next;
    }
    n->next = l2.head;
    l1.size = l1.size + l2.size;
    
    return l1;
}

List tail(List l){
    if (l.head == NULL) {
        return l;
    } else {
        Node* n = l.head->next;
        free(l.head);
        l.head = n;
        l.size -= 1;
        return l;
    }
}

XY* list_to_arr(List l, XY* p){
    if (l.head == NULL) return NULL;

    p = malloc((l.size + 1)* sizeof(XY));
    
    for (int i = 0; i<l.size; i++) {
        p[i] = l.head->elem;
        l = tail(l);
    }
    XY last = {1000,1000};
    p[l.size] = last;
    
    return p;
}

List destroy_list(List l){

    Node * n = l.head;

    if (l.head == NULL) return l;
    while (n != NULL) {
        l.head = l.head->next;
        free(n);
        n = l.head;
    }
    l.size = 0;

    return l;
}