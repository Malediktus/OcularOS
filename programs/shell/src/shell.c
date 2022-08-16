#include "shell.h"
#include "config.h"
#include <OcularOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    // TODO: free arguments
    // TODO: allow arguments to use quotes
    print("OcularOS v1.0.0\n");
    while (1)
    {
        print("> ");
        char buf[SHELL_MAX_INPUT_SIZE];
        ocularos_readline(buf, sizeof(buf), true);
        print("\n");

        system(buf);
    }

    return 0;
}