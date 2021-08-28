#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdio.h>

typedef struct BINARY_HEAP
{
    int key;
    struct BINARY_HEAP * left;
    struct BINARY_HEAP * right;
    struct BINARY_HEAP * parent;
}*binary_heap;


binary_heap init(binary_heap heap);

binary_heap insert(binary_heap heap,int key);

binary_heap delete_heap(binary_heap heap,int key);



#endif