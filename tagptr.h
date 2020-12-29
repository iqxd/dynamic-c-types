#pragma once
#include "config.h"

typedef uint64_t var_t;

#define HEAP_OBJECT_BYTES 24
#define SHORT_STR_ALLOC_BYTES (HEAP_OBJECT_BYTES-1)
#define LIST_RESERVED_ELEMS 10
#define LIST_INCR_FACTOR 1.8

#define TAG_ALLOC_BITS 6
#define TAG_SHIFT_BITS (64-TAG_ALLOC_BITS)
#define POS_FLOAT_ALLOC_BITS 63
#define POS_FLOAT_TAG_LEAST (1<<(TAG_ALLOC_BITS-1))
#define INT_BITS_MASK       0x00000000FFFFFFFF
#define REF_BITS_MASK       0x0000FFFFFFFFFFFF
#define POS_FLOAT_BITS_MASK 0x7FFFFFFFFFFFFFFF

typedef enum {
    T_INT = 0,
    T_NONE,
    T_NFLOAT,
    T_LSTR,
    T_SSTR,
    T_LIST,
    T_DICT,
    T_PFLOAT = POS_FLOAT_TAG_LEAST
} type_t;

#define TAG_NULL (((var_t)T_NONE) << TAG_SHIFT_BITS)

typedef struct {
    double val;
    void* unused[2];
} nfloat_t;

typedef struct {
    char val[SHORT_STR_ALLOC_BYTES];
    uint8_t len;
} sstr_t;

typedef struct {
    size_t len;
    char* val;
    size_t* refcnt;
} lstr_t;

typedef struct {
    size_t len;
    var_t* elem;
    size_t alloc;
} list_t;

static_assert(sizeof(nfloat_t) <= HEAP_OBJECT_BYTES, "");
static_assert(sizeof(sstr_t) <= HEAP_OBJECT_BYTES, "");
static_assert(sizeof(lstr_t) <= HEAP_OBJECT_BYTES, "");
static_assert(sizeof(list_t) <= HEAP_OBJECT_BYTES, "");

static inline var_t build_tag_ptr(void* raw, type_t tag)
{
    return (var_t)raw | ((var_t)tag << TAG_SHIFT_BITS);
}

static inline type_t get_tag(var_t v)
{
    return (v >> POS_FLOAT_ALLOC_BITS) ? POS_FLOAT_TAG_LEAST : (v >> TAG_SHIFT_BITS);
}

static inline void* get_ref(var_t v)
{
    return (void*)(v & REF_BITS_MASK);
}

static inline void* _new_heap_obj()
{
    return malloc(HEAP_OBJECT_BYTES);
}

static inline void* _clone_heap_obj(var_t v)
{
    return memcpy(_new_heap_obj(), get_ref(v), HEAP_OBJECT_BYTES);
}

static inline void _delete_heap_obj(var_t* v_ref)
{
    free(get_ref(*v_ref));
    *v_ref = TAG_NULL;
}

static inline var_t set_int(int32_t val)
{
    return build_tag_ptr(NULL, T_INT) | (uint32_t)val;
}

static inline int32_t get_int(var_t v)
{
    return (int32_t)(v & INT_BITS_MASK);
}

static inline var_t set_float(double val)
{
    if (val < 0)
    {
        nfloat_t* raw = malloc(sizeof(nfloat_t));
        raw->val = val;
        return build_tag_ptr(raw, T_NFLOAT);
    }
    // most floating numbers used in common case are positive, 
    // so use tagged value in the pointer to avoid heap allocation.
    return (*(var_t*)&val) | build_tag_ptr(NULL, T_PFLOAT);
}

static inline double get_pos_float(var_t v)
{
    return *(double*)(&(var_t) { v & POS_FLOAT_BITS_MASK });
}

static inline double get_neg_float(var_t v)
{
    return *(double*)get_ref(v);
}

static inline var_t set_str(const char* val)
{
    size_t len = strlen(val);
    if (len < SHORT_STR_ALLOC_BYTES)
    {
        sstr_t* raw = malloc(sizeof(sstr_t));
        strcpy(raw->val, val);
        raw->len = (uint8_t)len;
        return build_tag_ptr(raw, T_SSTR);
    }
    else
    {
        lstr_t* raw = malloc(sizeof(lstr_t));
        raw->len = len;
        raw->val = malloc((len + 1) * sizeof(char));
        strcpy(raw->val, val);
        raw->refcnt = malloc(sizeof(size_t));
        *(raw->refcnt) = 1;
        return build_tag_ptr(raw, T_LSTR);
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

typedef struct {
    size_t(*size_func)(var_t);
    void (*print_func)(var_t);
    var_t(*clone_func)(var_t);
    void (*delete_func)(var_t*);
} tagfunc_t;

tagfunc_t tagfunc_arr[POS_FLOAT_TAG_LEAST + 1];

// print funcs
void Print(var_t);
void print_int(var_t);
void print_pos_float(var_t);
void print_neg_float(var_t);
void print_short_str(var_t);
void print_long_str(var_t);

// size funcs
size_t Size(var_t);
size_t size_int(var_t);
size_t size_pos_float(var_t);
size_t size_neg_float(var_t);
size_t size_short_str(var_t);
size_t size_long_str(var_t);

// clone funcs
var_t Clone(var_t);
var_t clone_int(var_t);
var_t clone_pos_float(var_t);
var_t clone_neg_float(var_t);
var_t clone_short_str(var_t);
var_t clone_long_str(var_t);

// delete funcs
void Delete(var_t*);
void delete_int(var_t*);
void delete_pos_float(var_t*);
void delete_neg_float(var_t*);
void delete_short_str(var_t*);
void delete_long_str(var_t*);