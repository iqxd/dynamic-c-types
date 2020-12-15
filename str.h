#pragma once
#include "var.h"

type_t StrType, SStrType;

str_t new_str(char*);

void delete_str(str_t);
var_t* clone_str(str_t);
void print_str(str_t);