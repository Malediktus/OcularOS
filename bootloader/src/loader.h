#ifndef LOADER_H
#define LOADER_H

#include <config.h>
#include <status.h>
#include <lib/types.h>
#include <lib/screen.h>
#include <lib/string.h>
#include <lib/memory.h>
#include <port.h>
#include <heap/kheap.h>
#include <disk/disk.h>
#include <disk/diskstream.h>
#include <disk/pathparser.h>
#include <disk/file.h>

void loader_main();
void panic(const char* msg);

#endif