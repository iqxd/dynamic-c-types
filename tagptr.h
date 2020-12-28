#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif

#define HEAP_OBJECT_BYTES 24
#define SHORT_STR_ALLOC_BYTES 23
#define LIST_RESERVED_ELEMS 10
#define LIST_INCR_FACTOR 1.8
#define DICT_KEY_ALLOC_BYTES 24
#define DICT_RESERVED_NODES 16

typedef uint64_t tagptr_t;
#define TAG_NULL ((tagptr_t)0)
#define TAG_ALLOC_BITS 6
#define TAG_SHIFT_BITS (64-TAG_ALLOC_BITS)
#define POS_FLOAT_SHIFT_BITS 1
#define POS_FLOAT_TAG_LEAST (1<<(TAG_ALLOC_BITS-1))
#define INT_BITS_MASK       0x00000000FFFFFFFF
#define REF_BITS_MASK       0x0000FFFFFFFFFFFF
#define POS_FLOAT_BITS_MASK 0x7FFFFFFFFFFFFFFF

typedef enum {
    T_INT = 0 ,
    T_NONE,
    T_NEG_FLOAT,
    T_LSTR,
    T_SSTR,
    T_LIST,
    T_DICT,
    T_POS_FLOAT = POS_FLOAT_TAG_LEAST
} tag_t;

typedef struct {
    double val;
    void* unused[2];
} tnfloat_t;

typedef struct {
    char val[SHORT_STR_ALLOC_BYTES];
    char len;
} tsstr_t;

typedef struct {
    size_t len;
    char* val;
    size_t* refcnt;
} tlstr_t;

typedef struct {
    size_t len;
    tagptr_t* elem;
    size_t alloc;
} tlist_t;


static_assert(sizeof(tnfloat_t) <= HEAP_OBJECT_BYTES, "");
static_assert(sizeof(tsstr_t) <= HEAP_OBJECT_BYTES, "");
static_assert(sizeof(tlstr_t) <= HEAP_OBJECT_BYTES, "");
static_assert(sizeof(tlist_t) <= HEAP_OBJECT_BYTES, "");

static inline tagptr_t build_tag_ptr(void* raw, tag_t tag)
{
    return (tagptr_t)raw | ((tagptr_t)tag << TAG_SHIFT_BITS);
}

static inline tag_t get_tag(tagptr_t tp)
{
    return (tag_t)(tp >> TAG_SHIFT_BITS);
}

static inline void* get_ref(tagptr_t tp)
{
    return (void*)(tp & REF_BITS_MASK );
}

static inline void* _new_heap_obj()
{
    return malloc(HEAP_OBJECT_BYTES);
}

static inline void* _clone_heap_obj(tagptr_t tp)
{
    return memcpy(_new_heap_obj(), get_ref(tp), HEAP_OBJECT_BYTES);
}

static inline void _delete_heap_obj(tagptr_t* tp_ref)
{
    free(get_ref(*tp_ref));
    *tp_ref = TAG_NULL;
}

static inline tagptr_t set_int(int32_t val)
{
    return build_tag_ptr(NULL, T_INT) | (uint32_t)val;
}

static inline int32_t get_int(tagptr_t tp)
{
    return (int32_t)(tp & INT_BITS_MASK);
}

static inline tagptr_t set_float(double val)
{
    if (val < 0)
    {
        tnfloat_t* raw = malloc(sizeof(tnfloat_t));
        raw->val = val;
        return build_tag_ptr(raw, T_NEG_FLOAT);
    }
    // most floating numbers used in common case are positive, 
    // so use tagged value in the pointer to avoid heap allocation.
    return (*(tagptr_t*)&val) | build_tag_ptr(NULL, T_POS_FLOAT);  
}

static inline double get_float(tagptr_t tp)
{
    tag_t tag = get_tag(tp);
    if (tag >= T_POS_FLOAT)
        return *(double*)(&(tagptr_t){ tp & POS_FLOAT_BITS_MASK });
    else if (tag == T_NEG_FLOAT)
        return *(double*)get_ref(tp);
}

static inline double get_pos_float(tagptr_t tp)
{
    return *(double*)(&(tagptr_t){ tp & POS_FLOAT_BITS_MASK });
}

static inline double get_neg_float(tagptr_t tp)
{
    return *(double*)get_ref(tp);
}

static inline tagptr_t set_str(const char* val)
{
    size_t len = strlen(val);
    if ( len < SHORT_STR_ALLOC_BYTES )
    {
        tsstr_t* raw = malloc(sizeof(tsstr_t));
        strcpy(raw->val, val);
        raw->len = len;
        return build_tag_ptr(raw, T_SSTR);
    } 
    else 
    {
        tlstr_t* raw = malloc(sizeof(tlstr_t));
        raw->len = len;
        raw->val = malloc((len + 1) * sizeof(char));
        strcpy(raw->val, val);
        raw->refcnt = malloc(sizeof(size_t));
        *(raw->refcnt) = 1;
        return build_tag_ptr(raw, T_LSTR);
    } 
}

static inline char* get_str(tagptr_t tp)
{
    tag_t tag = get_tag(tp);
    void* ref = get_ref(tp);
    if (tag == T_SSTR)
        return ((tsstr_t*)ref)->val;
    else if (tag == T_LSTR)
        return ((tlstr_t*)ref)->val;
}

static inline char* get_short_str(tagptr_t tp)
{
    return ((tsstr_t*)get_ref(tp))->val;
}

static inline char* get_long_str(tagptr_t tp)
{
    return ((tlstr_t*)get_ref(tp))->val;
}

typedef struct {
    size_t(*size_func)(tagptr_t);
    void (*print_func)(tagptr_t);
    tagptr_t (*clone_func)(tagptr_t);
    void (*delete_func)(tagptr_t);
} tagfunc_t;

tagfunc_t tagfunc_arr[POS_FLOAT_TAG_LEAST+1];

// print funcs
void print_int(tagptr_t);
void print_pos_float(tagptr_t);
void print_neg_float(tagptr_t);
void print_short_str(tagptr_t);
void print_long_str(tagptr_t);

// size funcs
size_t size_int(tagptr_t);
size_t size_pos_float(tagptr_t);
size_t size_neg_float(tagptr_t);
size_t size_short_str(tagptr_t);
size_t size_long_str(tagptr_t);

// clone funcs
tagptr_t clone_int(tagptr_t);
tagptr_t clone_pos_float(tagptr_t);
tagptr_t clone_neg_float(tagptr_t);
tagptr_t clone_short_str(tagptr_t);
tagptr_t clone_long_str(tagptr_t);

// delete funcs
void delete_int(tagptr_t*);
void delete_pos_float(tagptr_t*);
void delete_neg_float(tagptr_t*);
void delete_short_str(tagptr_t*);
void delete_long_str(tagptr_t*);