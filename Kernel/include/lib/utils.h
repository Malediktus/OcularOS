#ifndef MOS_UTILS_H
#define MOS_UTILS_H

#include "types.h"

void printf(char* str);
void printfHex(uint8_t key);

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);
void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);

#endif