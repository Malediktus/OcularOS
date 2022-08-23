#ifndef ISR80H_FILE_H
#define ISR80H_FILE_H

#include <task/task.h>
#include <filesystem/file.h>
#include <config.h>

void* isr80h_command14_fopen(struct interrupt_frame* frame);
void* isr80h_command15_fseek(struct interrupt_frame* frame);
void* isr80h_command16_fread(struct interrupt_frame* frame);
void* isr80h_command17_fwrite(struct interrupt_frame* frame);
void* isr80h_command18_fstat(struct interrupt_frame* frame);
void* isr80h_command19_fclose(struct interrupt_frame* frame);

#endif