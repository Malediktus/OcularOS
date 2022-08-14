#ifndef TYPES_H
#define TYPES_H

#define NULL ((void *)0)

#include <stdbool.h>

typedef char                int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long int            int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long int   uint64_t;

typedef uint32_t            size_t;

struct psf1_header
{
    uint8_t magic[2];
    uint8_t mode;
    uint8_t charsize;
};

struct psf1_font
{
    struct psf1_header* header;
    void* buffer;
};

#endif