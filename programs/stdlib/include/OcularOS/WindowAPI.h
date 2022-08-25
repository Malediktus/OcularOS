#ifndef LIBC_WINDOWAPI_H
#define LIBC_WINDOWAPI_H

#include <stdbool.h>

struct ipc_buffer
{
    // general info and event stuff
    unsigned int size; // Set by the kernel
    unsigned int bitmap_for_events; // Fist 4 for wm, last 4 for program
    long event_space[8];

    // header
    unsigned char has_frame;
    unsigned char active;
    unsigned int window_width;
    unsigned int window_height;
    int x;
    int y;
    char title[20];

    // framebuffer
    int pixels[1024 * 768];
};

typedef struct ipc_buffer* Window;

Window create_window(int width, int height, char* title, bool has_frame);
int* get_framebuffer(Window window);
void set_mouse_click_event(Window window, unsigned int button);
int poll_mouse_click_event(Window window);

void set_mouse_move_event(Window window, unsigned int x, unsigned int y);
int* poll_mouse_move_event(Window window);

void set_window_size(Window window, unsigned int width, unsigned int height);
void window_update(Window window);
void window_shutdown(Window window);

#endif