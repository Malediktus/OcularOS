#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

typedef uint32_t size_t;

#define NULL ((void *)0)

#define ERROR(value) (void*)(value)
#define ERROR_I(value) (int)(value)
#define ISERROR(value) ((int)value < 0)

#endif