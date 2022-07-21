#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10
#define OCULAROS_TOTAL_INTERRUPTS 512

// 100MB heap size
#define OCULAROS_HEAP_SIZE_BYTES 104857600
#define OCULAROS_HEAP_BLOCK_SIZE 4096
#define OCULAROS_HEAP_ADDRESS 0x01000000
#define OCULAROS_HEAP_TABLE_ADDRESS 0x0007ffff

#define OCULAROS_SECTOR_SIZE 512

#endif