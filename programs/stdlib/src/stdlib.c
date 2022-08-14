#include "stdlib.h"
#include "OcularOS.h"

void* ocularos_malloc(size_t size);
void ocularos_free(void* ptr);

void* malloc(size_t size)
{
    return ocularos_malloc(size);
}

void free(void* ptr)
{
    ocularos_free(ptr);
}

char* itoa(int i)
{
    static char text[12];
    int loc = 11;
    text[11] = 0;
    char neg = 1;
    if (i >= 0)
    {
        neg = 0;
        i = -i;
    }

    while (i)
    {
        text[--loc] = '0' - (i % 10);
        i /= 10;
    }

    if (loc == 11)
        text[--loc] = '0';

    if (neg)
        text[--loc] = '-';
    
    return &text[loc];
}