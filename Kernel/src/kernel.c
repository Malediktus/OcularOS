#include "../include/hardware/gdt.h"
#include "../include/lib/types.h"
#include "../include/hardware/isr.h"
#include "../include/lib/timer.h"
#include "../include/driver/keyboard.h"
#include "../include/hardware/pci.h"
#include "../include/driver/ata.h"
#include "../include/filesystem/msdospart.h"

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;
    
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }
        
        if(x >= 80)
        {
            x = 0;
            y++;
        }
        
        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

typedef void (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;
extern void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern void kernelMain(const void* multiboot_structure, unsigned int multiboot_magic)
{
    init_gdt();

    isr_install();

    asm volatile("sti");
    //init_timer(10);
    //init_keyboard();
    //SelectDrivers();

    struct ATA ata0m;
    struct ATA ata0s;
    struct ATA ata1m;
    struct ATA ata1s;

    // interrupt 14
    init_ata(&ata0m, 0x1F0, 1);
    printf("Primary master: ");
    identify_ata(ata0m);
    init_ata(&ata0s, 0x1F0, 0);
    printf("\nPrimary slave: ");
    identify_ata(ata0s);

    printf("\n\n\n");

    ReadPartitions(ata0s);
    //flush(ata0s);
    //read_ata(ata0s, 0, 512);

    // interrupt 15
    //init_ata(ata1m, 0x170, 1);
    //init_ata(ata1s, 0x170, 0);

    // third: 0x1E8
    // fourth: 0x168

    while(1);
}