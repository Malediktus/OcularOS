#ifndef MOS_KEYBOARD_H
#define MOS_KEYBOARD_H

#include "../lib/types.h"
#include "../lib/utils.h"
#include "../hardware/port.h"
#include "../hardware/isr.h"

static void keyboard_callback(registers_t regs);

void init_keyboard();

#endif