#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <limits.h>
#include <OcularOS.h>
#include <OcularOS/WindowAPI.h>
#include "backend/sysfunction.h"

Window dragged_window = 0;
Window focused_window = 0;
int cursor_x = 512, cursor_y = 384;
bool mouse_button1 = false;
bool mouse_button_tab1 = false;

int rgb_to_hex(int r, int b, int g)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
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
}

void render_windows(Window* windows)
{
    for (int i = 0; i <= 10; i++)
    {
        if (windows[i] == 0)
            continue;
        
        if (windows[i]->active == 0)
        {
            free(windows[i]);
            windows[i] = 0;
            continue;
        }

        if (windows[i]->has_frame == 1)
        {
        fillrect(windows[i]->x, windows[i]->y, windows[i]->window_width, 20, 0x7f8585);
        
        if (mouse_button1 | mouse_button_tab1)
        {
            if ((cursor_x >= windows[i]->x && cursor_x <= windows[i]->x+windows[i]->window_width) && (cursor_y >= windows[i]->y && cursor_y <= windows[i]->y+20))
            {
                dragged_window = windows[i];
                focused_window = windows[i];
            }
        }

        draw_subbuffer(windows[i]->x, windows[i]->y+20, windows[i]->window_width, windows[i]->window_height, windows[i]->pixels);
        if ((cursor_x >= windows[i]->x && cursor_x <= windows[i]->x+windows[i]->window_width) && (cursor_y >= windows[i]->y+20 && cursor_y <= windows[i]->y+20+windows[i]->window_height))
        {
            if (mouse_button1 | mouse_button_tab1)
            {
                focused_window = windows[i];
                set_mouse_click_event(windows[i], 1);
            }
            set_mouse_move_event(windows[i], cursor_x-windows[i]->x, cursor_y-windows[i]->y);
        }
        windows[i]->active -= 1;
        }
        else
        {
            draw_subbuffer(windows[i]->x, windows[i]->y, windows[i]->window_width, windows[i]->window_height, windows[i]->pixels);
            if ((cursor_x >= windows[i]->x && cursor_x <= windows[i]->x+windows[i]->window_width) && (cursor_y >= windows[i]->y && cursor_y <= windows[i]->y+windows[i]->window_height))
            {
                if (mouse_button1 | mouse_button_tab1)
                {
                    focused_window = windows[i];
                    set_mouse_click_event(windows[i], 1);
                }
                set_mouse_move_event(windows[i], cursor_x-windows[i]->x, cursor_y-windows[i]->y);
            }
            windows[i]->active -= 1;
        }
    }
}

int main(int argc, char** argv)
{
    Window* windows = malloc(10*sizeof(Window));
    mouse_button1 = false;
    mouse_button_tab1 = false;
    dragged_window = 0;

    FILE img = fopen("0:/cur.tga", "r");
    struct file_stat stats;
    fstat(img, &stats);
    unsigned char* img_buf = malloc(stats.filesize);
    fread(img_buf, stats.filesize, 1, img);
    fclose(img);
    unsigned int* pix_data = tga_parse(img_buf, stats.filesize);

    img = fopen("0:/bg.tga", "r");
    fstat(img, &stats);
    img_buf = malloc(stats.filesize);
    fread(img_buf, stats.filesize, 1, img);
    fclose(img);
    unsigned int* bg_pix_data = tga_parse(img_buf, stats.filesize);
    unsigned int* bg_pix_data_scaled_width = malloc((bg_pix_data[0] * bg_pix_data[1] * 8 * 8) + 2);
    unsigned int* bg_pix_data_scaled = malloc((bg_pix_data[0] * bg_pix_data[1] * 8 * 8 * 8) + 2);
    for (int i = 2, j = 0; i < (bg_pix_data[0]*bg_pix_data[1])+2; i++, j += 8)
    {
        bg_pix_data_scaled_width[j] = bg_pix_data[i];
        bg_pix_data_scaled_width[j+1] = bg_pix_data[i];
        bg_pix_data_scaled_width[j+2] = bg_pix_data[i];
        bg_pix_data_scaled_width[j+3] = bg_pix_data[i];
        bg_pix_data_scaled_width[j+4] = bg_pix_data[i];
        bg_pix_data_scaled_width[j+5] = bg_pix_data[i];
        bg_pix_data_scaled_width[j+6] = bg_pix_data[i];
        bg_pix_data_scaled_width[j+7] = bg_pix_data[i];
    }

    for (int i = 0, j = 0; i < (bg_pix_data[0]*bg_pix_data[1]*8); i += bg_pix_data[0]*8, j += bg_pix_data[0]*8*8)
    {
        for (int d = 0; d < (bg_pix_data[0]*8); d++)
        {
            bg_pix_data_scaled[j+d] = bg_pix_data_scaled_width[i+d];
            bg_pix_data_scaled[j+d+(bg_pix_data[0]*8)] = bg_pix_data_scaled_width[i+d];
            bg_pix_data_scaled[j+d+(bg_pix_data[0]*8*2)] = bg_pix_data_scaled_width[i+d];
            bg_pix_data_scaled[j+d+(bg_pix_data[0]*8*3)] = bg_pix_data_scaled_width[i+d];
            bg_pix_data_scaled[j+d+(bg_pix_data[0]*8*4)] = bg_pix_data_scaled_width[i+d];
            bg_pix_data_scaled[j+d+(bg_pix_data[0]*8*5)] = bg_pix_data_scaled_width[i+d];
            bg_pix_data_scaled[j+d+(bg_pix_data[0]*8*6)] = bg_pix_data_scaled_width[i+d];
            bg_pix_data_scaled[j+d+(bg_pix_data[0]*8*7)] = bg_pix_data_scaled_width[i+d];
        }
    }

    system("1");
    system("dock.elf");
    while(1)
    {
        draw_subbuffer(0, 0, bg_pix_data[0]*8, bg_pix_data[1]*8, (int*)(bg_pix_data_scaled));
        void* ptr = ocularos_pop_ipc();
        if (ptr != 0)
        {
            for (int i = 0; i <= 10; i++)
            {
                if (windows[i] == 0)
                {
                    printf("Connection accepted at %i\n", (int)ptr);
                    windows[i] = ptr;
                    windows[i]->x = 512;
                    windows[i]->y = 384;
                    focused_window = windows[i];
                    break;
                }
            }
        }

        render_windows(windows);
        draw_subbuffer(cursor_x, cursor_y, pix_data[0], pix_data[1], (int*)(pix_data+2));

        if (mouse_button_tab1)
        {
            mouse_button_tab1 = false;
            dragged_window = 0;
        }

        switch(ocularos_getkey())
        {
        case 0:
            break;
        case 13: // Enter
            if (mouse_button1)
            {
                mouse_button1 = false;
                dragged_window = 0;
            }
            else
            {
                mouse_button1 = true;
            }
            break;
        case ' ': // Space
            mouse_button_tab1 = true;
            break;
        case '-': // Up arrow
            cursor_y -= 10;
            if (dragged_window)
                dragged_window->y -= 10;
            break;
        case '0': // Down arrow
            cursor_y += 10;
            if (dragged_window)
                dragged_window->y += 10;
            break;
        case '6': // Left arrow
            cursor_x -= 10;
            if (dragged_window)
                dragged_window->x -= 10;
            break;
        case '1': // Right arrow
            cursor_x += 10;
            if (dragged_window)
                dragged_window->x += 10;
            break;
        default:
            break;
        }

        print("Mouse button: ");
        if (mouse_button1)
        {
            print("X");
        }
        else
        {
            print("O");
        }

        swap_buffers();
    }
    
    free(windows);
    return 0;
}