#pragma once
#include "var.h"

#define LIST_RESERVED_ELEMS 10
#define LIST_INCR_FACTOR 1.8

typedef struct {
    _Alignas(8) size_t len;
    _Alignas(8) var_t* elems;
    _Alignas(8) size_t alloc;
} list_t;

static_assert(sizeof(list_t) == HEAP_OBJECT_BYTES, "");

static inline var_t set_empty_list()
{
    list_t* raw = _new_heap_obj();
    raw->len = 0;
    raw->alloc = LIST_RESERVED_ELEMS;
    raw->elems = checked_malloc(raw->alloc * sizeof(var_t));
    return build_var(raw, T_LIST);
}

static inline void list_index_error(size_t index,size_t length)
{
    fprintf(stderr, "runtime error: index [%zu] exceeds list length [%zu]", index, length);
    runtime_error();
}

var_t set_list(var_t[],size_t);

void print_list(var_t);
size_t size_list(var_t);
var_t clone_list(var_t);
void delete_list(var_t*);

void list_add(var_t,var_t);
var_t list_get(var_t, size_t);
void list_update(var_t, size_t, var_t);
void list_remove(var_t, size_t);
var_t list_pop(var_t);
void list_clear(var_t);
bool  list_empty(var_t);
