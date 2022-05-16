#ifndef MOS_GDT_H
#define MOS_GDT_H

#include "../lib/types.h"

#define NULL_SEGMENT 0
#define CODE_SEGMENT 1
#define DATA_SEGMENT 2

struct GDT
{
    uint16_t segment_limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct GDT_PTR
{
    uint16_t limit_size;
    struct GDT* base_address;
} __attribute__((packed));

extern struct GDT gdt_entries[3];
extern struct GDT_PTR gdt_first;

extern void init_gdt();

#endif