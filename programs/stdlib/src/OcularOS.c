#include "OcularOS.h"
#include <stdbool.h>

int ocularos_getkey();
void ocularos_putchar(char c);

int ocularos_getkeyblock()
{
    int val = 0;
    do
    {
        val = ocularos_getkey();
    }
    while (val == 0);
    return val;
}

void ocularos_readline(char* out, int max, bool output_while_typing)
{
    int i = 0;
    for (i = 0; i < max-1; i++)
    {
        char key = ocularos_getkeyblock();

        // Carriage return
        if (key == 13)
            break;

        if (output_while_typing)
            ocularos_putchar(key);

        // Backspace
        if (key == 0x08 && i >= 1)
        {
            out[i-1] = 0x00;
            i -= 2;
            continue;
        }

        out[i] = key;
    }

    //Add the null terminator
    out[i] = 0x00;
}