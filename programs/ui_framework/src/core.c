#include "ui_core.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>

uint32_t framebuffer = 0;
uint32_t back_buffer = 0;
uint16_t pitch = 0;
uint8_t bpp = 0;
uint16_t width = 0;
uint16_t height = 0;
struct psf1_font* terminal_font;

void terminal_initialize(uint32_t _framebuffer, uint16_t _pitch, uint8_t _bpp, uint16_t _width, uint16_t _height)
{
    int font = fopen("0:/kfont.psf", "r");
    if (!font)
        while (1);

    struct psf1_header* font_header = malloc(sizeof(struct psf1_header));
    struct psf1_font* kernel_font = malloc(sizeof(struct psf1_font));
    fread(font_header, sizeof(struct psf1_header), 1, font);
    kernel_font->header = font_header;

    if (font_header->magic[0] != 0x36 || font_header->magic[1] != 0x04)
        while (1); // Font file invalid

    uint32_t fontBufferSize = font_header->charsize * 256;
    if (font_header->mode == 1) // 512 glyph mode
        fontBufferSize = font_header->charsize * 512;
    
    void* font_buffer = malloc(fontBufferSize);
    fread(font_buffer, fontBufferSize, 1, font);
    fclose(font);

    kernel_font->buffer = font_buffer;
    terminal_font = kernel_font;

    framebuffer = _framebuffer;
    back_buffer = (uint32_t)malloc(width * height * (bpp/8));
    pitch = _pitch;
    bpp = _bpp;
    width = _width;
    height = _height;
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

void putpixel(int x, int y, int color)
{
    *((uint32_t*)(y * pitch + (x * (bpp/8)) + framebuffer)) = color;
}

void fillrect(int x, int y, int width, int height, int color)
{
    for (int i = y; i < y+height; i++) {
        for (int j = x; j < x+width; j++) {
            *((uint32_t*)(i * pitch + (j * (bpp/8)) + framebuffer)) = color;
        } // TODO: Dont calculate ptr all the time
    }
}

void draw_subbuffer(int pos_x, int pos_y, int width, int height, int* buffer)
{
    int l = 0;
    for (int y = pos_y; y < pos_y+height; y++)
    {
        for (int x = pos_x; x < pos_x+width; x++)
        {
            int alpha = (buffer[l] >> (8*3)) & 0xff;
            if (alpha > 0x00)
            {
                *((uint32_t*)(y * pitch + (x * (bpp/8)) + framebuffer)) = buffer[l];
            }
            l++;
        }
    } // TODO: Dont calculate ptr all the time
}

void fillscreen(int color)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            putpixel(x, y, color);
        }
    }
}

void swap_buffers()
{
    memcpy((uint32_t*)framebuffer, (uint32_t*)back_buffer, width * height * (bpp/8));
}

unsigned int *tga_parse(unsigned char *ptr, int size) // From osdev.org
{
    unsigned int *data;
    int i, j, k, x, y, w = (ptr[13] << 8) + ptr[12], h = (ptr[15] << 8) + ptr[14], o = (ptr[11] << 8) + ptr[10];
    int m = ((ptr[1]? (ptr[7]>>3)*ptr[5] : 0) + 18);
 
    if(w<1 || h<1) return NULL;
 
    data = (unsigned int*)malloc((w*h+2)*sizeof(unsigned int));
    if(!data) return NULL;
 
    switch(ptr[2]) {
        case 1:
            if(ptr[6]!=0 || ptr[4]!=0 || ptr[3]!=0 || (ptr[7]!=24 && ptr[7]!=32)) { free(data); return NULL; }
            for(y=i=0; y<h; y++) {
                k = ((!o?h-y-1:y)*w);
                for(x=0; x<w; x++) {
                    j = ptr[m + k++]*(ptr[7]>>3) + 18;
                    data[2 + i++] = ((ptr[7]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                }
            }
            break;
        case 2:
            if(ptr[5]!=0 || ptr[6]!=0 || ptr[1]!=0 || (ptr[16]!=24 && ptr[16]!=32)) { free(data); return NULL; }
            for(y=i=0; y<h; y++) {
                j = ((!o?h-y-1:y)*w*(ptr[16]>>3));
                for(x=0; x<w; x++) {
                    data[2 + i++] = ((ptr[16]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                    j += ptr[16]>>3;
                }
            }
            break;
        case 9:
            if(ptr[6]!=0 || ptr[4]!=0 || ptr[3]!=0 || (ptr[7]!=24 && ptr[7]!=32)) { free(data); return NULL; }
            y = i = 0;
            for(x=0; x<w*h && m<size;) {
                k = ptr[m++];
                if(k > 127) {
                    k -= 127; x += k;
                    j = ptr[m++]*(ptr[7]>>3) + 18;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[7]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                    }
                } else {
                    k++; x += k;
                    while(k--) {
                        j = ptr[m++]*(ptr[7]>>3) + 18;
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[7]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                    }
                }
            }
            break;
        case 10:
            if(ptr[5]!=0 || ptr[6]!=0 || ptr[1]!=0 || (ptr[16]!=24 && ptr[16]!=32)) { free(data); return NULL; }
            y = i = 0;
            for(x=0; x<w*h && m<size;) {
                k = ptr[m++];
                if(k > 127) {
                    k -= 127; x += k;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[16]==32?ptr[m+3]:0xFF) << 24) | (ptr[m+2] << 16) | (ptr[m+1] << 8) | ptr[m];
                    }
                    m += ptr[16]>>3;
                } else {
                    k++; x += k;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[16]==32?ptr[m+3]:0xFF) << 24) | (ptr[m+2] << 16) | (ptr[m+1] << 8) | ptr[m];
                        m += ptr[16]>>3;
                    }
                }
            }
            break;
        default:
            free(data); return NULL;
    }
    data[0] = w;
    data[1] = h;
    return data;
};