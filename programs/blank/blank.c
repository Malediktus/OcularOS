#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);
    
    if (argc >= 2 && strncmp(argv[1], "fault", 5) == 0)
    {
        int* ptr = (int*)0x01;
        *ptr = 0xBAD;
    }
        
    return 0;
}