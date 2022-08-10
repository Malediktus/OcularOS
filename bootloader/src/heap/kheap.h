#ifndef KHEAP_H
#define KHEAP_H

#include <heap/heap.h>
#include <lib/screen.h>

void kheap_init();
void* kmalloc(size_t size);
void* kzalloc(size_t size);
void kfree(void* ptr);

#endif