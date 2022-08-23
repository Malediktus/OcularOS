#ifndef LIBC__STDLIB_H
#define LIBC__STDLIB_H

#include <stddef.h>

void* malloc(size_t size);
void free(void* ptr);
int system(const char *command);

char* itoa(int i);
char* ftoa(double f, int precision);

typedef int FILE;

struct file_stat
{
    unsigned int flags;
    unsigned int filesize;
};
enum
{
    SEEK_SET,
    SEEK_CUR,
    SEEK_END
};

FILE fopen(char* filename, char* mode_str);
int fseek(FILE fd, int offset, unsigned int whence);
int fread(void* ptr, unsigned int size, unsigned int nmemb, FILE fd);
int fwrite(void* ptr, unsigned int size, unsigned int nmemb, FILE fd);
int fstat(FILE fd, struct file_stat* stat);
int fclose(FILE fd);

#endif