#ifndef MOS_MSDOSPART_H
#define MOS_MSDOSPART_H

#include "../lib/utils.h"
#include "../driver/ata.h"
#include "fat32.h"
        
struct PartitionTableEntry
{
    uint8_t bootable;

    uint8_t start_head;
    uint8_t start_sector : 6;
    uint16_t start_cylinder : 10;

    uint8_t partition_id;

    uint8_t end_head;
    uint8_t end_sector : 6;
    uint16_t end_cylinder : 10;
            
    uint32_t start_lba;
    uint32_t length;
} __attribute__((packed));

struct MasterBootRecord
{
    uint8_t bootloader[440];
    uint32_t signature;
    uint16_t unused;
            
    struct PartitionTableEntry primaryPartition[4];
            
    uint16_t magicnumber;
} __attribute__((packed));

void ReadPartitions(struct ATA ata);

#endif