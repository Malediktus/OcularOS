#ifndef KERNEL_H
#define KERNEL_H

#include <hardware/idt.h>
#include <hardware/gdt.h>
#include <memory/kheap.h>
#include <memory/paging.h>
#include <lib/memory.h>
#include <lib/string.h>
#include <lib/screen.h>
#include <syscall/isr80h.h>
#include <task/task.h>
#include <task/process.h>
#include <task/tss.h>
#include <filesystem/file.h>
#include <filesystem/pparser.h>
#include <driver/disk/disk.h>
#include <driver/keyboard/keyboard.h>
#include <driver/mouse/mouse.h>
#include <driver/disk/streamer.h>
#include <config.h>
#include <types.h>
#include <status.h>

struct environment_variable
{
    char* name;
    char* content;
};

int set_environment_variable(char* key, char* content);
char* get_environment_variable(char* key);

void kernel_main();

void panic(const char* msg);
void kernel_page();
void kernel_registers();

#define ERROR(value) (void*)(value)
#define ERROR_I(value) (int)(value)
#define ISERR(value) ((int)value < 0)
#endif