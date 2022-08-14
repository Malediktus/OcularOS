#include <OcularOS.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
        printf("%s\n", argv[i]);

    print("Ok\n");

    return 0;
}