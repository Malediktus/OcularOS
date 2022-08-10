#include <loader.h>

void loader_main()
{
    terminal_initialize();

    // Initializing the heap
    kheap_init();

    // Initializing the filesystems
    fs_init();

    // Search and initialize the disks
    disk_search_and_init();

    int kernel = fopen("0:/kernel.bin", "r");
    if (!kernel)
        panic("Couldn't find kernel.bin: Error 0x01");
    struct file_stat kernel_stats;
    fstat(kernel, &kernel_stats);

    char* kernel_buffer = (char*)0x0100000;
    fread(kernel_buffer, kernel_stats.filesize, 1, kernel);
    fclose(kernel);
    ((void (*)()) kernel_buffer)();
    while (1);
}

void panic(const char* msg)
{
    print("A ciritcal error occured... Cannot boot your system!\n");
    print(msg);
    while (1);
}