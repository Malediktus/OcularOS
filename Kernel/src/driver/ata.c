#include "../../include/driver/ata.h"
#include "../../include/hardware/port.h"
#include "../../include/lib/utils.h"

void init_ata(struct ATA* ata, uint16_t portBase, int master) {
    ata->dataPort = portBase;
    ata->errorPort = portBase + 1;
    ata->sectorCountPort = portBase + 2;
    ata->lbaLowPort = portBase + 3;
    ata->lbaMidPort = portBase + 4;
    ata->lbaHiPort = portBase + 5;
    ata->devicePort = portBase + 6;
    ata->commandPort = portBase + 7;
    ata->controlPort = portBase + 0x206;

    ata->bytesPerSector = 512;
    ata->master = master;
}

void identify_ata(struct ATA ata) {
    port_byte_out(ata.devicePort, ata.master ? 0xA0 : 0xB0);
    port_byte_out(ata.controlPort, 0);
    port_byte_out(ata.devicePort, 0xA0);
    uint8_t status = port_byte_in(ata.commandPort);
    if(status == 0xFF)
        return;
    
    port_byte_out(ata.devicePort, ata.master ? 0xA0 : 0xB0);
    port_byte_out(ata.sectorCountPort, 0);
    port_byte_out(ata.lbaLowPort, 0);
    port_byte_out(ata.lbaMidPort, 0);
    port_byte_out(ata.lbaHiPort, 0);
    port_byte_out(ata.commandPort, 0xEC);

    status = port_byte_in(ata.commandPort);
    if(status == 0x00) { // no device
        printf("Disk not found");
        return;
    }
    
    while(((status & 0x80) == 0x80) && ((status & 0x01) != 0x01))
        status = port_byte_in(ata.commandPort);
    
    if(status & 0x01) {
        printf("Error identifing disk!");
        return;
    }

    for(uint16_t i = 0; i < 256; i++) {
        uint16_t data = port_byte_in(ata.dataPort);
        char* foo = "  \0";
        foo[1] = (data >> 8) & 0x00FF;
        foo[0] = data & 0x00FF;
        printf(foo);
    }
}

void read_ata(struct ATA ata, uint32_t sector, uint8_t* data, int count)
{
    if(sector & 0xF0000000)
        return;
    if(count > ata.bytesPerSector)
        return;
    
    port_byte_out(ata.devicePort, (ata.master ? 0xE0 : 0xF0) | ((sector & 0x0F000000) >> 24));
    port_byte_out(ata.errorPort, 0);
    port_byte_out(ata.sectorCountPort, 1);
    
    port_byte_out(ata.lbaLowPort, sector & 0x000000FF);
    port_byte_out(ata.lbaMidPort, (sector & 0x0000FF00) >> 8);
    port_byte_out(ata.lbaHiPort, (sector & 0x00FF0000) >> 16);
    port_byte_out(ata.commandPort, 0x20);
    
    
    
    uint8_t status = port_byte_in(ata.commandPort);
    while(((status & 0x80) == 0x80)
        && ((status & 0x01) != 0x01))
        status = port_byte_in(ata.commandPort);
    
    if(status & 0x01)
    {
        printf("ERROR");
        return;
    }
    
    //printf("Reading from ATA: ");
    
    for(uint16_t i = 0; i < count; i+= 2)
    {
        uint16_t wdata = port_word_in(ata.dataPort);

        /*
        char* foo = "  \0";
        foo[1] = (wdata >> 8) & 0x00FF;
        foo[0] = wdata & 0x00FF;
        printf(foo);
        */
        
        data[i] = wdata & 0x00FF;
        if(i+1 < count)
            data[i+1] = (wdata >> 8) & 0x00FF;
    }
    
    for(uint16_t i = count + (count % 2); i < ata.bytesPerSector; i+= 2)
        port_word_in(ata.dataPort);
}

void write_ata(struct ATA ata, uint32_t sectorNum, uint8_t* data, uint32_t count) {
    if(sectorNum > 0x0FFFFFFF)
        return;
    if(count > 512)
        return;
    
    
    port_byte_out(ata.devicePort, (ata.master ? 0xE0 : 0xF0) | ((sectorNum & 0x0F000000) >> 24));
    port_byte_out(ata.errorPort, 0);
    port_byte_out(ata.sectorCountPort, 1);
    port_byte_out(ata.lbaLowPort, sectorNum & 0x000000FF);
    port_byte_out(ata.lbaMidPort, (sectorNum & 0x0000FF00) >> 8);
    port_byte_out(ata.lbaLowPort, (sectorNum & 0x00FF0000) >> 16);
    port_byte_out(ata.commandPort, 0x30);
    
    printf("Writing to ATA Drive: ");

    for(int i = 0; i < count; i += 2)
    {
        uint16_t wdata = data[i];
        if(i+1 < count)
            wdata |= ((uint16_t)data[i+1]) << 8;
        port_word_out(ata.dataPort, wdata);
        
        char *text = "  \0";
        text[0] = (wdata >> 8) & 0xFF;
        text[1] = wdata & 0xFF;
        printf(text);
    }
    
    for(int i = count + (count%2); i < 512; i += 2)
        port_word_out(ata.dataPort, 0x0000);
}

void flush(struct ATA ata) {
    port_byte_out(ata.devicePort, ata.master ? 0xE0 : 0xF0);
    port_byte_out(ata.commandPort, 0xE7);

    uint8_t status = port_byte_in(ata.commandPort);
    if(status == 0x00)
        return;
    
    while(((status & 0x80) == 0x80)
       && ((status & 0x01) != 0x01))
        status = port_byte_in(ata.commandPort);
        
    if(status & 0x01)
    {
        printf("Error flushing disk!");
        return;
    }
}