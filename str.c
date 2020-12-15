#include "str.h"

type_t StrType = { .tp = STR, .print_func = print_var, .clone_func = clone_var , .delete_func=delete_var};
type_t SStrType = {.tp = SSTR, .print_func = print_var , .clone_func = clone_var};

str_t new_str(char* cp)
{
    size_t len = strlen(cp);
    if (len < 16) {
        str_t s = { &SStrType };
        strcpy(s.sval, cp);
        return s;
    }
    else {
        return (str_t) { &StrType, .len = len, .sref = strdup(cp) };
    }
}

var_t* clone_str(str_t s)
{
    return s.type->clone_func((var_t*)&s);
}

void delte_str(str_t s)
{
    s.type->delete_func((var_t*)&s);
}

void print_str(str_t s)
{
    s.type->print_func((var_t *)&s);
}
