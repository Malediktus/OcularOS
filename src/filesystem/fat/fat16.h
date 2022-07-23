#ifndef FAT16_H
#define FAT16_H

#include <filesystem/file.h>
#include <lib/string.h>
#include <drivers/diskstream.h>

struct filesystem* fat16_init();

#endif