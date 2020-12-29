#pragma once

#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define HEAP_OBJECT_BYTES 24
#define ALLOCATOR_RESERVED_OBJECTS 100
#define ALLOCATOR_INCREMENT_OBJECTS 50