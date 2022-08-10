#ifndef PATHPARSER_H
#define PATHPARSER_H

#include <lib/string.h>
#include <lib/memory.h>
#include <heap/kheap.h>
#include <status.h>

struct path_root
{
    int drive_no;
    struct path_part* first;
};

struct path_part
{
    const int8_t* part;
    struct path_part* next;
};

struct path_root* pathparser_parse(const char* path, const char* current_directory_path);
void pathparser_free(struct path_root* root);

#endif