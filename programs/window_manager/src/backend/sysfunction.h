#ifndef SYSFUNCTION_H
#define SYSFUNCTION_H

void putpixel(int x, int y, int color);
void fillrect(int x, int y, int w, int h, int color);
void draw_subbuffer(int x, int y, int w, int h, int* buffer);
void swap_buffers();

#endif