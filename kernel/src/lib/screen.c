#include <lib/screen.h>

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;
uint16_t pitch = 0;
uint8_t bpp = 0;
uint32_t framebuffer = 0;
struct psf1_font* terminal_font;
uint16_t width = 0;
uint16_t height = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int xOff, int yOff, char c, int colour)
{
    char* font_ptr = terminal_font->buffer + (c * terminal_font->header->charsize);
    font_ptr += 4; // Dont know why, but this helps
    for (uint32_t y = yOff; y < yOff + 16; y++) {
        for (uint32_t x = xOff; x < xOff+8; x++) {
            if ((*font_ptr & (0b10000000 >> (x - xOff))) > 0)
                putpixel(x, y, colour);
        }
        font_ptr++;
    }
}

void terminal_backspace()
{
    if (terminal_row == 0 && terminal_col == 0)
    {
        return;
    }

    if (terminal_col == 0)
    {
        terminal_row -= 16;
        terminal_col = width;
    }

    terminal_col -= 8;
    for (int y = 0; y <= 16; y++)
        for (int x = 0; x <= 8; x++)
            putpixel(terminal_col+x, terminal_row+y, 0x4351D2);
    terminal_writechar(' ', 0xFFFFFF);
    terminal_col -= 8;
}

void terminal_writechar(char c, int colour)
{
    if (c == '\n')
    {
        terminal_row += 16;
        terminal_col = 0;
        return;
    }

    if (c == 0x08)
    {
        terminal_backspace();
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 8;
    if (terminal_col >= width)
    {
        terminal_col = 0;
        terminal_row += 16;
    }
}

void terminal_initialize()
{
    int font = fopen("0:/kfont.psf", "r");
    if (!font)
        while (1);

    struct psf1_header* font_header = kzalloc(sizeof(struct psf1_header));
    struct psf1_font* kernel_font = kzalloc(sizeof(struct psf1_font));
    fread(font_header, sizeof(struct psf1_header), 1, font);
    kernel_font->header = font_header;

    if (font_header->magic[0] != 0x36 || font_header->magic[1] != 0x04)
        while (1); // Font file invalid

    uint32_t fontBufferSize = font_header->charsize * 256;
    if (font_header->mode == 1) // 512 glyph mode
        fontBufferSize = font_header->charsize * 512;
    
    void* font_buffer = kzalloc(fontBufferSize);
    fread(font_buffer, fontBufferSize, 1, font);
    fclose(font);

    kernel_font->buffer = font_buffer;
    terminal_font = kernel_font;

    struct vbe_mode_info_structure* graphics_info = (struct vbe_mode_info_structure*)0x00000500;
    pitch = graphics_info->pitch;
    bpp = graphics_info->bpp;
    framebuffer = graphics_info->framebuffer;
    width = graphics_info->width;
    height = graphics_info->height;
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    fillscreen(0x4351D2);
}

void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 0xFFFFFF);
    }
}

void putpixel(int x, int y, int color)
{
    *((uint32_t*)(y * pitch + (x * (bpp/8)) + framebuffer)) = color;
}

void fillscreen(int color)
{
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            putpixel(x, y, color);
        }
    }
}

void draw_icon(int x, int y, int w, int h, uint32_t* pixels) {
    int l, j, i;
    for (l = j = 0; l < h; l ++) {
        for (i = 0; i < w; i ++, j++) {
            putpixel(x + i, y + l, pixels[j]);
        }
    }
}