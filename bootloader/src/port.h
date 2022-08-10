#ifndef PORT_H
#define PORT_h

#include <lib/types.h>

uint8_t insb(uint16_t port);
uint16_t insw(uint16_t port);

void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);

#endif