#include "../../include/driver/keyboard.h"

static void keyboard_callback(registers_t regs) {
    uint8_t scancode = port_byte_in(0x60);
    printf("Keyboard interrupts");
    printfHex(scancode);
    printf(" ");
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}