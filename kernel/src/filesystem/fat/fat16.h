#ifndef FAT16_H
#define FAT16_H

#include <filesystem/file.h>
#include <lib/string.h>
#include <driver/disk/disk.h>
#include <driver/disk/streamer.h>
#include <memory/kheap.h>
#include <lib/memory.h>
#include <status.h>
#include <kernel.h>
#include <types.h>

struct filesystem* fat16_init();

#endif