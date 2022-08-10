#ifndef FAT16_H
#define FAT16_H

#include <disk/file.h>
#include <lib/string.h>
#include <disk/diskstream.h>

struct filesystem* fat16_init();

#endif