#include <stdlib.h>
#include <stdio.h>
#include <ui_core.h>
#include <OcularOS.h>
#include <OcularOS/WindowAPI.h>

int main(int argc, char** argv)
{
    bool connected = false;
    char* pipe;
    Window window = create_window(400, 300, "test", true);
    printf("Connecting with window manager at %i\n", (int)window);
    if (!window)
        print("Error connecting with window manager\n");
    int* framebuffer = get_framebuffer(window);

    terminal_initialize((uint32_t)framebuffer, window->window_width*sizeof(int), sizeof(int)*8, window->window_width, window->window_height);
    fillscreen(0xff000000);

    system("1");
    system("shell.elf");

    while (1)
    {
        if (!connected)
        {
            pipe = ocularos_pop_ipc();
            if (pipe != 0)
                connected = true;
            continue;
        }
        if (pipe[0] != 0)
        {
            terminal_putchar(0, 10, pipe[0], 0xffffffff);
        }
        window_update(window);
    }

    window_shutdown(window);
    return 0;
}