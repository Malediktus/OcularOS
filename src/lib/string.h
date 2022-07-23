#ifndef STRING_H
#define STRING_H

#include <lib/types.h>

typedef const char* string;

char tolower(char s1);
int strlen(string str);
int strnlen(const char* ptr, int max);
int strnlen_terminator(const char* str, int max, char terminator);
int istrncmp(const char* s1, const char* s2, int n);
int strncmp(const char* str1, const char* str2, int n);
char* strcpy(char* dest, const char* src);
bool isdigit(char c);
int tonumericdigit(char c);

#endif