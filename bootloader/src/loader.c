#include <loader.h>

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

void printHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    print(foo);
}

static void putpixel(int x, int y, int color, uint16_t pitch, uint8_t bpp, uint32_t framebuffer)
{
    *((uint32_t*)(y * pitch + (x * (bpp/8)) + framebuffer)) = color;
}

void loader_main()
{
    terminal_initialize();

    //struct vbe_mode_info_structure* graphics_info = (struct vbe_mode_info_structure*)0x00000500;

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