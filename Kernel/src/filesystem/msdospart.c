#include "../../include/filesystem/msdospart.h"

void ReadPartitions(struct ATA ata)
{
    struct MasterBootRecord mbr;
    
    printf("MBR: ");
    
    read_ata(ata, 0, (uint8_t*)&mbr, sizeof(struct MasterBootRecord));

    /*
    for(int i = 0x1BE; i <= 0x01FF; i++)
    {
        printfHex(((uint8_t*)&mbr)[i]);
        printf(" ");
    }
    printf("\n");
    */
    
    if(mbr.magicnumber != 0xAA55)
    {
        printf("illegal MBR");
        return;
    }
    
    
    for(int i = 0; i < 4; i++)
    {
        if(mbr.primaryPartition[i].partition_id == 0x00)
            continue;
        
        printf(" Partition ");
        printfHex(i & 0xFF);
        
        
        if(mbr.primaryPartition[i].bootable == 0x80)
            printf(" bootable. Type");
        else
            printf(" not bootable. Type ");
        
        
        printfHex(mbr.primaryPartition[i].partition_id);
        
     
        ReadBiosBlock(ata, mbr.primaryPartition[i].start_lba);
    }
}