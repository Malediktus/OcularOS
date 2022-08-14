#ifndef ISR80H_H
#define ISR80H_H

#include <hardware/idt.h>
#include <syscall/misc.h>
#include <syscall/io.h>
#include <syscall/heap.h>

enum SystemCommands
{
    SYSTEM_COMMAND0_SUM,
    SYSTEM_COMMAND1_PRINT,
    SYSTEM_COMMAND2_GETKEY,
    SYSTEM_COMMAND3_PUTCHAR,
    SYSTEM_COMMAND4_MALLOC,
    SYSTEM_COMMAND5_FREE,
    SYSTEM_COMMAND6_PROCESS_LOAD,
    SYSTEM_COMMAND7_INVOKE_SYSTEM_COMMAND,
    SYSTEM_COMMAND8_GET_PROGRAM_ARGUMENTS,
    SYSTEM_COMMAND9_EXIT,
    SYSTEM_COMMAND10_GET_EXIT,
};

void isr80h_register_commands();

#endif