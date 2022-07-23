#ifndef KERNEL_H
#define KERNEL_H

#include <config.h>
#include <status.h>
#include <lib/types.h>
#include <lib/screen.h>
#include <lib/string.h>
#include <lib/memory.h>
#include <hardware/idt.h>
#include <hardware/port.h>
#include <memory/kheap.h>
#include <memory/paging.h>
#include <drivers/disk.h>
#include <drivers/diskstream.h>
#include <filesystem/pathparser.h>
#include <filesystem/file.h>

void kernel_main();
void panic(const char* msg);

#endif