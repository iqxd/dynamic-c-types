#pragma once
#include "var.h"

#define LIST_RESERVED_ELEMS 10
#define LIST_INCR_FACTOR 1.8

typedef struct {
    size_t len;
    var_t* elem;
    size_t alloc;
} list_t;

static_assert(sizeof(list_t) <= HEAP_OBJECT_BYTES, "");

static inline var_t set_list(size_t init_size)
{
    list_t* raw = _new_heap_obj();
    raw->elem = NULL;
    raw->len = 0;
    raw->alloc = init_size < LIST_RESERVED_ELEMS ? LIST_RESERVED_ELEMS : (init_size * LIST_INCR_FACTOR);
    return build_var(raw, T_LIST);
}

// list_t* new_list(var_t*[],size_t);

// void delete_list(list_t*);
// var_t* clone_list(list_t*);
// void print_list(list_t*);

// void list_add(list_t* , var_t*);
// var_t* list_get(list_t* , size_t);
// void list_update(list_t* , size_t , var_t*);
// void list_remove(list_t* , size_t);
// void list_pop(list_t* );
// void list_clear(list_t* );