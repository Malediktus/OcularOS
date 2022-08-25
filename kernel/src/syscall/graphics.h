#ifndef ISR80H_GRAPHICS_H
#define ISR80H_GRAPHICS_H

#include <lib/screen.h>

void* isr80h_command13_putpixel(struct interrupt_frame* frame);
void* isr80h_command22_fillrect(struct interrupt_frame* frame);
void* isr80h_command23_swap_buffers(struct interrupt_frame* frame);
void* isr80h_command24_draw_subbuffer(struct interrupt_frame* frame);

#endif