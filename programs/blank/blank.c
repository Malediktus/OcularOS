#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <OcularOS.h>
#include "OcularOS/WindowAPI.h"

int main(int argc, char** argv)
{
    Window window = create_window(200, 100, "test", true);
    printf("Connecting with window manager at %i\n", (int)window);
    if (!window)
        print("Error connecting with window manager\n");
    int* framebuffer = get_framebuffer(window);
    int i = 0;
    for (int y = 10; y <= 80; y++)
    {
        for (int x = 10; x <= 100; x++)
        {
            int* pixel = framebuffer + y * window->window_width + x;
            *pixel = 0x00FF0000;
            i++;
        }
    }
    while (1)
    {
        if (poll_mouse_click_event(window));
        int* mouse_pos = poll_mouse_move_event(window);
        if (mouse_pos != 0)
            ;//set_window_size(window, mouse_pos[0]+10, mouse_pos[1]+10);
        window_update(window);
    }

    window_shutdown(window);
    return 0;
}