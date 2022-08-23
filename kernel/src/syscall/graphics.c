#include <syscall/graphics.h>
#include <lib/string.h>

void* isr80h_command13_putpixel(struct interrupt_frame* frame)
{
    int x = (int)task_get_stack_item(task_current(), 0);
    int y = (int)task_get_stack_item(task_current(), 1);
    int color = (int)task_get_stack_item(task_current(), 2);

    putpixel(x, y, color);

    return 0;
}