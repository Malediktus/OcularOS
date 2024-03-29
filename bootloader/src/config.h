#ifndef CONFIG_H
#define CONFIG_H

// 100MB heap size
#define OCULARBOOT_HEAP_SIZE_BYTES 104857600
#define OCULARBOOT_HEAP_BLOCK_SIZE 4096
#define OCULARBOOT_HEAP_ADDRESS 0x01000000
#define OCULARBOOT_HEAP_TABLE_ADDRESS 0x0007ffff

#define OCULARBOOT_SECTOR_SIZE 512
#define OCULARBOOT_MAX_PATH 108

#define OCULARBOOT_MAX_FILESYSTEMS 12
#define OCULARBOOT_MAX_FILE_DESCRIPTORS 512

#endif