#include <OcularOS.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    print("Hello from C, finally back again with libc\n");

    char* ptr = malloc(20);
    strcpy(ptr, "hello world");
    print(ptr);
    free(ptr);
    
    while(1);
    return 0;
}