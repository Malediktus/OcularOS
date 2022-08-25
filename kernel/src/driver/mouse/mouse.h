#ifndef MOUSE_H
#define MOUSE_H

#include <hardware/port.h>
#include <hardware/idt.h>
#include <types.h>

#define MOUSE_DATA_PORT 0x60
#define MOUSE_COMMAND_PORT 0x64

void mouse_init();
void mouse_interrupt();

#endif