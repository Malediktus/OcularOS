#include <driver/keyboard/keyboard.h>

static struct keyboard* keyboard_list_head = 0;
static struct keyboard* keyboard_list_last = 0;

void keyboard_init()
{
    keyboard_insert(classic_init());
}

int keyboard_insert(struct keyboard* keyboard)
{
    int res = 0;
    if (keyboard->init == 0)
    {
        res = -EINVARG;
        goto out;
    }

    if (keyboard_list_last)
    {
        keyboard_list_last->next = keyboard;
        keyboard_list_last = keyboard;
    }
    else
    {
        keyboard_list_head = keyboard;
        keyboard_list_last = keyboard;
    }

    res = keyboard->init();

out:
    return res;
}

static int keyboard_get_tail_index(struct process* process)
{
    return process->keyboard.tail % sizeof(process->keyboard.buffer);
}

void keyboard_backspace(struct process* process)
{
    process->keyboard.tail -= 1;
    int real_index = keyboard_get_tail_index(process);
    process->keyboard.buffer[real_index] = 0x00;
}

void keyboard_set_capslock(struct keyboard* keyboard, keyboard_caps_lock_state state)
{
    keyboard->capslock_state = state;
}

keyboard_caps_lock_state keyboard_get_capslock(struct keyboard* keyboard)
{
    return keyboard->capslock_state;
}

void keyboard_push(char c)
{
    for (int i = 0; i < OCULAROS_MAX_PROCESSES; i++)
    {
    struct process* process = processes[i];
    if (!process)
    {
        continue;
    }

    if (c == 0)
        return;

    int real_index = keyboard_get_tail_index(process);
    process->keyboard.buffer[real_index] = c;
    process->keyboard.tail++;
    }
}

char keyboard_pop()
{
    if (!task_current())
    {
        return 0;
    }

    struct process* process = task_current()->process;
    int real_index = process->keyboard.head % sizeof(process->keyboard.buffer);
    char c = process->keyboard.buffer[real_index];
    if (c == 0x00)
    {
        return 0;
    }

    process->keyboard.buffer[real_index] = 0;
    process->keyboard.head++;
    return c;
}