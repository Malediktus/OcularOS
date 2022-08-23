#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <OcularOS.h>

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);
    
    if (argc >= 2 && strncmp(argv[1], "fault", 5) == 0)
    {
        int* ptr = (int*)0x01;
        *ptr = 0xBAD;
    }

    int i = 0;
    while(1)
    {
        if (ocularos_pop_ipc() != 0)
        {
            print("ok");
        }
        if (i != 2)
        {
            i++;
            system("ocwm.elf");
        }
    }
        
    return 0;
}