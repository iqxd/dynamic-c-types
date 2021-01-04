#pragma once
#include "var.h"

#define SHORT_STR_ALLOC_BYTES (HEAP_OBJECT_BYTES-1)

typedef struct {
    char val[SHORT_STR_ALLOC_BYTES];
    uint8_t len;
} sstr_t;

typedef struct {
    alignas(8) size_t len;
    alignas(8) char* val;
    alignas(8) size_t* refcnt;
} lstr_t;

static_assert(sizeof(sstr_t) == HEAP_OBJECT_BYTES, "");
static_assert(sizeof(lstr_t) == HEAP_OBJECT_BYTES, "");

static inline var_t set_str(const char* val)
{
    size_t len = strlen(val);
    if (len < SHORT_STR_ALLOC_BYTES)
    {
        sstr_t* raw = _new_heap_obj();
        strcpy(raw->val, val);
        raw->len = (uint8_t)len;
        return build_var(raw, T_SSTR);
    }
    else
    {
        lstr_t* raw = _new_heap_obj();
        raw->len = len;
        raw->val = checked_malloc((len + 1) * sizeof(char));
        strcpy(raw->val, val);
        raw->refcnt = checked_malloc(sizeof(size_t));
        *(raw->refcnt) = 1;
        return build_var(raw, T_LSTR);
    }
}

static inline char* get_short_str(var_t v)
{
    return ((sstr_t*)get_ref(v))->val;
}

static inline char* get_long_str(var_t v)
{
    return ((lstr_t*)get_ref(v))->val;
}

static inline size_t size_long_str(var_t v)
{
    lstr_t* lstr = get_ref(v);
    return size_heap_var(v) + (lstr->len + 1) + sizeof(*(lstr->refcnt));
}

static inline var_t clone_long_str(var_t v)
{
    lstr_t* lstr = _clone_heap_obj(v);
    (*lstr->refcnt)++;
    return build_var(lstr, T_LSTR);
}

static inline void delete_long_str(var_t* v_ref)
{
    lstr_t* lstr = get_ref(*v_ref);
    if (--(*lstr->refcnt) == 0)
    {
        free(lstr->val);
        free(lstr->refcnt);
    }
    free(lstr);
    *v_ref = VAR_NULL;
}

static inline void print_short_str(var_t v)
{
    printf("%16.16llX => \"%s\"\n", v, get_short_str(v));
}

static inline void print_long_str(var_t v)
{
    printf("%16.16llX => \"%s\"\n", v, get_long_str(v));
}
