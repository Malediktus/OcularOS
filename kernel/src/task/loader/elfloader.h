#ifndef ELFLOADER_H
#define ELFLOADER_H

#include <task/loader/elf.h>
#include <filesystem/file.h>
#include <lib/memory.h>
#include <lib/string.h>
#include <memory/kheap.h>
#include <memory/paging.h>
#include <kernel.h>
#include <status.h>
#include <types.h>
#include <config.h>

struct elf_file
{
    char filename[OCULAROS_MAX_PATH];
    int in_memory_size;

    /**
     * The physical memory address that this elf file is loaded at
    **/
    void* elf_memory;

    /**
     * The virtual address of this binary
    **/
    void* virtual_base_address;
    void* virtual_end_address;

    void* physical_base_address;
    void* physical_end_address;
};

void* elf_virtual_base(struct elf_file* file);
void* elf_virtual_end(struct elf_file* file);
void* elf_phys_base(struct elf_file* file);
void* elf_phys_end(struct elf_file* file);
struct elf_header* elf_header(struct elf_file* file);
struct elf32_shdr* elf_sheader(struct elf_header* header);
struct elf32_phdr* elf_pheader(struct elf_header* header);
struct elf32_phdr* elf_program_header(struct elf_header* header, int index);
struct elf32_shdr* elf_section(struct elf_header* header, int index);
void* elf_phdr_phys_address(struct elf_file* file, struct elf32_phdr* phdr);
void* elf_memory(struct elf_file* file);
int elf_load(const char* filename, struct elf_file** file_out);
void elf_close(struct elf_file* file);

#endif