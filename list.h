#pragma once
#include "var.h"

#define ListSizeIncrFactor 1.8

type_t ListType;

list_t* new_list(var_t*[],size_t);

void print_list(list_t*);