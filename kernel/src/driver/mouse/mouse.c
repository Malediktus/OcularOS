#include <driver/mouse/mouse.h>

void mouse_init()
{
    idt_register_interrupt_callback(0x2C, mouse_interrupt);

    outb(MOUSE_COMMAND_PORT, 0xA8);
}

void mouse_interrupt()
{
    kernel_page();
    print("Mouse interrupt\n");

    uint8_t status = insb(MOUSE_COMMAND_PORT);
    if (!(status & 0x20))
    {
        print("Mouse error\n");
        task_page();
        return;
    }
    insb(MOUSE_DATA_PORT);

    task_page();
}