#ifndef LIBC__STDLIB_H
#define LIBC__STDLIB_H

#include <stddef.h>

void* malloc(size_t size);
void free(void* ptr);

char* itoa(int i);

#endif