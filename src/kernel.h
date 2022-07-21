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

void kernel_main();

#endif