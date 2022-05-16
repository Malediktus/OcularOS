#ifndef MOS_ATA_H
#define MOS_ATA_H

#include "../lib/types.h"
#include "../hardware/port.h"

struct ATA {
    uint16_t dataPort; // 16-Bit
    uint16_t errorPort; // 8-Bit
    uint16_t sectorCountPort;
    uint16_t lbaLowPort;
    uint16_t lbaMidPort;
    uint16_t lbaHiPort;
    uint16_t devicePort;
    uint16_t commandPort;
    uint16_t controlPort;

    int master;
    uint16_t bytesPerSector;
};

void init_ata(struct ATA* ata, uint16_t portBase, int master);
void identify_ata(struct ATA ata);
void read_ata(struct ATA ata, uint32_t sector, uint8_t* data, int count);
void write_ata(struct ATA ata, uint32_t sectorNum, uint8_t* data, uint32_t count);
void flush(struct ATA ata);

#endif