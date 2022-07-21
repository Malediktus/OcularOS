#ifndef IDT_H
#define IDT_H

#include <lib/types.h>

struct idt_desc
{
    uint16_t offset_1;  // Offset bits 0 - 15
    uint16_t selector;  // Selector thats in our GDT
    uint8_t zero;       // Unused zero byte
    uint8_t type_attr;  // Descriptor type and attributes
    uint16_t offset_2;  // Offset bits 16 - 31
} __attribute__((packed));

struct idtr_desc
{
    uint16_t limit;     // Size of the descriptor table - 1
    uint32_t base;      // Base address of the start of the idt
} __attribute__((packed));

void idt_init();
void idt_set(int interrupt_no, void* address);
void enable_interrupts();
void disable_interrupts();

#endif