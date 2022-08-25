#include "OcularOS/WindowAPI.h"
#include "OcularOS.h"
#include "string.h"
#include "memory.h"
#include <limits.h>

typedef unsigned int word_t;
enum { BITS_PER_WORD = sizeof(word_t) * CHAR_BIT };
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b)  ((b) % BITS_PER_WORD)

void set_bit(word_t *words, int n) { 
    words[WORD_OFFSET(n)] |= (1 << BIT_OFFSET(n));
}

void clear_bit(word_t *words, int n) {
    words[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n)); 
}

int get_bit(word_t *words, int n) {
    word_t bit = words[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
    return bit != 0; 
}

Window create_window(int width, int height, char* title, bool has_frame)
{
    Window ptr = ocularos_start_ipc("0:/bin/ocwm.elf", sizeof(struct ipc_buffer));
    if (!ptr)
        return 0;
    ptr->active = 255;
    strncpy(ptr->title, title, 20);
    ptr->window_width = width;
    ptr->window_height = height;
    ptr->has_frame = has_frame ? 1 : 0;

    memset(ptr->pixels, 0xffffffff, 1024*768*(sizeof(int)));
    return ptr;
}

void window_update(Window window)
{
    window->active = 255;
}

void window_shutdown(Window window)
{
    window->active = 0;
}

int* get_framebuffer(Window window)
{
    return window->pixels;
}

void set_mouse_click_event(Window window, unsigned int button)
{
    set_bit(&window->bitmap_for_events, 0);
    ((int*)window->event_space)[0] = button;
}

int poll_mouse_click_event(Window window)
{
    if (get_bit(&window->bitmap_for_events, 0))
    {
        clear_bit(&window->bitmap_for_events, 0);
        return ((int*)window->event_space)[0];
    }
    return 0;
}

void set_mouse_move_event(Window window, unsigned int x, unsigned int y)
{
    set_bit(&window->bitmap_for_events, 1);
    ((int*)window->event_space)[2] = x;
    ((int*)window->event_space)[3] = y;
}

int* poll_mouse_move_event(Window window)
{
    static int temp[2];
    if (get_bit(&window->bitmap_for_events, 1))
    {
        clear_bit(&window->bitmap_for_events, 1);
        temp[0] = ((int*)window->event_space)[2];
        temp[1] = ((int*)window->event_space)[3];
        return temp;
    }
    return 0;
}

void set_window_size(Window window, unsigned int width, unsigned int height)
{
    window->window_width = width;
    window->window_height = height;
}