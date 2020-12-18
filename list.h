#pragma once
#include "var.h"

#define ListSizeIncrFactor 1.8

type_t ListType;

list_t* new_list(var_t*[],size_t);

void delete_list(list_t*);
var_t* clone_list(list_t*);
void print_list(list_t*);

void list_add(list_t* , var_t*);
var_t* list_get(list_t* , size_t);
void list_update(list_t* , size_t , var_t*);
void list_remove(list_t* , size_t);
void list_pop(list_t* );
void list_clear(list_t* );