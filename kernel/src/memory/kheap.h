#ifndef KHEAP_H
#define KHEAP_H

#include <memory/heap.h>
#include <lib/memory.h>
#include <types.h>
#include <config.h>
#include <kernel.h>

void kheap_init();
void* kmalloc(size_t size);
void* kzalloc(size_t size);
void kfree(void* ptr);

#endif