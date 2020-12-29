#pragma once
#include "config.h"

typedef struct _obj_node obj_node_t;

struct _obj_node {
    obj_node_t *next;
    char reserved[HEAP_OBJECT_BYTES];
};

typedef struct {
    size_t obj_count;
    obj_node_t *ready_slot;
    obj_node_t *head;
} allocator_t;

allocator_t Allocator;