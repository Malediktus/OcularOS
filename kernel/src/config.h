#ifndef CONFIG_H
#define CONFIG_H

#define OCULAROS_MAX_PATH 108

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define OCULAROS_TOTAL_INTERRUPTS 512

// 100MB heap size
#define OCULAROS_HEAP_SIZE_BYTES 104857600
#define OCULAROS_HEAP_BLOCK_SIZE 4096
#define OCULAROS_HEAP_ADDRESS 0x01000000 
#define OCULAROS_HEAP_TABLE_ADDRESS 0x00007E00

#define OCULAROS_SECTOR_SIZE 512

#define OCULAROS_MAX_FILESYSTEMS 12
#define OCULAROS_MAX_FILE_DESCRIPTORS 512

#define OCULAROS_MAX_PATH 108

#define OCULAROS_TOTAL_GDT_SEGMENTS 6

#define OCULAROS_PROGRAM_VIRTUAL_ADDRESS 0x400000
#define OCULAROS_USER_PROGRAM_STACK_SIZE 1024 * 16
#define OCULAROS_PROGRAM_VIRTUAL_STACK_ADDRESS_START 0x3FF000
#define OCULAROS_PROGRAM_VIRTUAL_STACK_ADDRESS_END OCULAROS_PROGRAM_VIRTUAL_STACK_ADDRESS_START - OCULAROS_USER_PROGRAM_STACK_SIZE

#define OCULAROS_MAX_PROGRAM_ALLOCATIONS 1024
#define OCULAROS_MAX_PROCESSES 12 // TODO: Increment number

#define USER_DATA_SEGMENT 0x23
#define USER_CODE_SEGMENT 0x1b

#define OCULAROS_MAX_ISR80H_COMMANDS 1024

#define OCULAROS_KEYBOARD_BUFFER_SIZE 1024
#define OCULAROS_MAX_ENVIRONMENT_VARIABLES 32
#define OCULAROS_MAX_ENVIRONMENT_VARIABLE_NAME 32
#define OCULAROS_MAX_ENVIRONMENT_VARIABLE_SIZE 108 // TODO: Increment number

#define OCULAROS_MAX_IPC_BUFFER_SIZE_PER_PROGRAM 32 // TODO: Increment number

#endif