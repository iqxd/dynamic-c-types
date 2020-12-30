#pragma once

#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif

#if defined(_MSC_VER) && defined(_DEBUG)
    #define LEAK_DEBUG
    #define _CRTDBG_MAP_ALLOC
#endif

#include <stdlib.h>

#ifdef LEAK_DEBUG
    #include <crtdbg.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define HEAP_OBJECT_BYTES 24
#define ALLOCATOR_RESERVED_OBJECTS 100
#define ALLOCATOR_INCREMENT_OBJECTS 50

static inline void* checked_malloc(size_t sz)
{
    void *raw = malloc(sz);
    if (raw) return raw;
    perror("malloc error");
    exit(EXIT_FAILURE);
}