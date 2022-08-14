#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_CAPS_ON 1
#define KEYBOARD_CAPS_OFF 0

typedef int keyboard_caps_lock_state;

#include <driver/keyboard/classic.h>
#include <task/process.h>
#include <task/task.h>
#include <status.h>
#include <kernel.h>

struct process;

typedef int (*KEYBOARD_INIT_FUNCTION)();

struct keyboard
{
    KEYBOARD_INIT_FUNCTION init;
    char name[20];

    keyboard_caps_lock_state capslock_state;
    struct keyboard* next;
};

void keyboard_init();
void keyboard_backspace(struct process* process);
void keyboard_set_capslock(struct keyboard* keyboard, keyboard_caps_lock_state state);
keyboard_caps_lock_state keyboard_get_capslock(struct keyboard* keyboard);
void keyboard_push(char c);
char keyboard_pop();
int keyboard_insert(struct keyboard* keyboard);

#endif