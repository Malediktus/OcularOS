#include <OcularOS.h>
#include <stdio.h>
#include "shell.h"

int main(int argc, char** argv)
{
    print("OcularOS v1.0.0\n");
    while (1)
    {
        print("> ");
        char buf[1024];
        ocularos_readline(buf, sizeof(buf), true);
        print("\n");

        ocularos_process_load(buf);
    }

    return 0;
}