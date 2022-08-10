#ifndef KEYBOARD_H
#define KEYBOARD_H

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
    struct keyboard* next;
};

void keyboard_init();
void keyboard_backspace(struct process* process);
void keyboard_push(char c);
char keyboard_pop();
int keyboard_insert(struct keyboard* keyboard);

#endif