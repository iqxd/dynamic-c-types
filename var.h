#pragma once
#include "config.h"

typedef struct _type type_t;

typedef enum
{
    NONE,
    INT,
    FLOAT,
    STR,
    SSTR,
    LIST,
    DICT
} type_id;

typedef struct {
    type_t *type;
} var_t;

struct _type {
    type_id tp;
    void (*print_func)(var_t*);
    var_t* (*clone_func)(var_t*);
    void (*delete_func)(var_t*);
};

typedef struct {
    type_t *type;
    union {
        int_t ival;
        double fval;
    };
} num_t;

typedef struct {
    type_t *type;
    union {
        char sval[SHORT_STR_ALLOC_BYTES];
        struct {
            size_t len;
            char *sref;
        };
    };
} str_t;

typedef struct {
    type_t *type;
    size_t len;
    size_t capacity;
    var_t *lref[];
} list_t;

typedef struct _dictnode dnode_t;

struct _dictnode {
    char key[DICT_KEY_ALLOC_BYTES];
    var_t* valp;
    dnode_t* left;
    dnode_t* right;
};

typedef struct {
    type_t* type;
    size_t len;
    dnode_t* root;
    dnode_t reserved[DICT_RESERVED_NODES];
} dict_t;

void print_var(var_t *);
var_t* clone_var(var_t*);
void delete_var(var_t*);