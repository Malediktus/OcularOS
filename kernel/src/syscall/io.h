#ifndef ISR80H_IO_H
#define ISR80H_IO_H

#include <task/task.h>
#include <driver/keyboard/keyboard.h>
#include <kernel.h>

struct interrupt_frame;
void* isr80h_command1_print(struct interrupt_frame* frame);
void* isr80h_command2_getkey(struct interrupt_frame* frame);
void* isr80h_command3_putchar(struct interrupt_frame* frame);
void* isr80h_command20_start_ipc(struct interrupt_frame* frame);
void* isr80h_command21_pop_ipc(struct interrupt_frame* frame);

#endif