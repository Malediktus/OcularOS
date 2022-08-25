#include <syscall/graphics.h>

void* isr80h_command13_putpixel(struct interrupt_frame* frame)
{
    int x = (int)task_get_stack_item(task_current(), 0);
    int y = (int)task_get_stack_item(task_current(), 1);
    int color = (int)task_get_stack_item(task_current(), 2);

    putpixel(x, y, color);

    return 0;
}

void* isr80h_command22_fillrect(struct interrupt_frame* frame)
{
    int x = (int)task_get_stack_item(task_current(), 0);
    int y = (int)task_get_stack_item(task_current(), 1);
    int w = (int)task_get_stack_item(task_current(), 2);
    int h = (int)task_get_stack_item(task_current(), 3);
    int color = (int)task_get_stack_item(task_current(), 4);
    fillrect(x, y, w, h, color);
    return 0;
}

void* isr80h_command23_swap_buffers(struct interrupt_frame* frame)
{
    swap_buffers();
    return 0;
}

void* isr80h_command24_draw_subbuffer(struct interrupt_frame* frame)
{
    int x = (int)task_get_stack_item(task_current(), 0);
    int y = (int)task_get_stack_item(task_current(), 1);
    int w = (int)task_get_stack_item(task_current(), 2);
    int h = (int)task_get_stack_item(task_current(), 3);
    int* user_space_buffer = task_get_stack_item(task_current(), 4);
    int* buffer = task_virtual_address_to_physical(task_current(), user_space_buffer);
    draw_subbuffer(x, y, w, h, buffer);
    return 0;
}