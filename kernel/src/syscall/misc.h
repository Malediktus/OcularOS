#ifndef ISR80H_MISC_H
#define ISR80H_MISC_H

#include <hardware/idt.h>
#include <task/task.h>
#include <config.h>
#include <status.h>

struct interrupt_frame;
void* isr80h_command0_sum(struct interrupt_frame* frame);
void* isr80h_command6_process_load(struct interrupt_frame* frame);

#endif