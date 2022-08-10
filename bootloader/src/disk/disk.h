#ifndef DISK_H
#define DISK_H

#include <port.h>
#include <lib/memory.h>
#include <disk/file.h>
#include <config.h>
#include <status.h>

typedef uint32_t OCULARBOOT_DISK_TYPE;

#define OCULARBOOT_DISK_TYPE_REAL 0 // Reppresents a real physical hard disk

struct disk
{
    OCULARBOOT_DISK_TYPE type;
    int sector_size;
    int id;
    struct filesystem* filesystem;

    // Private data of the filesystem
    void* fs_private;
};

void disk_search_and_init();
struct disk* disk_get(int index);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);

#endif