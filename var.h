#pragma once
#include "config.h"

typedef uint64_t var_t;

#define TAG_ALLOC_BITS 6
#define TAG_SHIFT_BITS (64-TAG_ALLOC_BITS)
#define REF_BITS_MASK     0x0000FFFFFFFFFFFF
#define POS_FLOAT_TAG_LEAST (1<<(TAG_ALLOC_BITS-1))
#define POS_FLOAT_ALLOC_BITS 63

typedef enum {
    T_NULL = 0,
    T_INT,
    T_NFLOAT,
    T_LSTR,
    T_SSTR,
    T_LIST,
    T_DICT,
    T_END,
    T_PFLOAT = POS_FLOAT_TAG_LEAST
} type_t;

var_t VAR_NULL;
var_t VAR_END;

static inline var_t build_var(void* raw, type_t tp)
{
    return (var_t)raw | ((var_t)tp << TAG_SHIFT_BITS);
}

static inline type_t get_type(var_t v)
{
    return (v >> POS_FLOAT_ALLOC_BITS) ? POS_FLOAT_TAG_LEAST : (v >> TAG_SHIFT_BITS);
}

static inline void* get_ref(var_t v)
{
    return (void*)(v & REF_BITS_MASK);
}

static inline void* _new_heap_obj()
{
    return checked_malloc(HEAP_OBJECT_BYTES);
}

static inline void* _clone_heap_obj(var_t v)
{
    return memcpy(_new_heap_obj(), get_ref(v), HEAP_OBJECT_BYTES);
}

static inline size_t size_tag_var(var_t v)
{
    return sizeof(v);
}

static inline size_t size_heap_var(var_t v)
{
    return sizeof(v) + HEAP_OBJECT_BYTES;
}

static inline var_t clone_tag_var(var_t v)
{
    return v;
}

static inline var_t clone_heap_var(var_t v)
{
    return build_var(_clone_heap_obj(v) , get_type(v));
}

static inline void delete_tag_var(var_t* v_ref)
{
    *v_ref = VAR_NULL;
}

static inline void delete_heap_var(var_t* v_ref)
{
    free(get_ref(*v_ref));
    *v_ref = VAR_NULL;
}

static inline void print_null(var_t v)
{
    printf("%16.16llX => %s\n", v, "NULL");
}


