#ifndef LIBC__OCULAROS_H
#define LIBC__OCULAROS_H

#include <stdbool.h>

void print(const char* message);
int ocularos_getkeyblock();
void ocularos_readline(char* out, int max, bool output_while_typing);
void ocularos_process_load(const char* filename);

#endif