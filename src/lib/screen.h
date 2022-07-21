#ifndef SCREEN_H
#define SCREEN_H

#include <lib/types.h>
#include <lib/string.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

void terminal_initialize();
void print(string str);

#endif