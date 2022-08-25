#ifndef UI_CORE_H
#define UI_CORE_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

extern uint16_t pitch;
extern uint8_t bpp;
extern uint32_t framebuffer;
extern uint16_t width;
extern uint16_t height;
extern uint16_t terminal_row;
extern uint16_t terminal_col;

struct psf1_header
{
    uint8_t magic[2];
    uint8_t mode;
    uint8_t charsize;
};

struct psf1_font
{
    struct psf1_header* header;
    void* buffer;
};

void terminal_initialize(uint32_t _framebuffer, uint16_t _pitch, uint8_t _bpp, uint16_t _width, uint16_t _height);
void terminal_putchar(int xOff, int yOff, char c, int colour);
void swap_buffers();
void fillscreen(int color);
void fillrect(int x, int y, int width, int height, int color);
void putpixel(int x, int y, int color);
void draw_subbuffer(int pos_x, int pos_y, int width, int height, int* buffer);
unsigned int *tga_parse(unsigned char *ptr, int size); // From osdev.org

#endif