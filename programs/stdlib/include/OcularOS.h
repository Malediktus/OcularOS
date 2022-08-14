#ifndef LIBC__OCULAROS_H
#define LIBC__OCULAROS_H

#include <stdbool.h>

struct command_argument
{
    char argument[512];
    struct command_argument* next;
};

void print(const char* message);
int ocularos_getkeyblock();
void ocularos_readline(char* out, int max, bool output_while_typing);
void ocularos_process_load(const char* filename);
int ocularos_system(struct command_argument* arguments);

#endif