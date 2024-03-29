#ifndef SCREEN_H
#define SCREEN_H

#include <lib/string.h>
#include <filesystem/file.h>
#include <config.h>
#include <types.h>

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

extern uint16_t pitch;
extern uint8_t bpp;
extern uint32_t framebuffer;
extern uint16_t width;
extern uint16_t height;
extern uint16_t terminal_row;
extern uint16_t terminal_col;

void putpixel(int x, int y, int color);
void fillrect(int x, int y, int width, int height, int color);
void terminal_initialize();
void terminal_writechar(char c, int colour);
void terminal_putchar(int xOff, int yOff, char c, int colour);
void print(const char* str);
void fillscreen(int color);
void draw_subbuffer(int x, int y, int width, int height, int* buffer);
void draw_icon(int x, int y, int w, int h, uint32_t* pixels);
void swap_buffers();

#endif