#ifndef ISR80H_GRAPHICS_H
#define ISR80H_GRAPHICS_H

#include <lib/screen.h>

void* isr80h_command13_putpixel(struct interrupt_frame* frame);

#endif