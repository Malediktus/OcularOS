#ifndef ISR80H_MISC_H
#define ISR80H_MISC_H

#include <hardware/idt.h>
#include <task/process.h>
#include <task/task.h>
#include <config.h>
#include <status.h>

struct interrupt_frame;
void* isr80h_command0_sum(struct interrupt_frame* frame);
void* isr80h_command6_process_load(struct interrupt_frame* frame);
void* isr80h_command7_invoke_system_command(struct interrupt_frame* frame);
void* isr80h_command8_get_program_arguments(struct interrupt_frame* frame);
void* isr80h_command9_exit(struct interrupt_frame* frame);
void* isr80h_command10_free_all(struct interrupt_frame* frame);

#endif