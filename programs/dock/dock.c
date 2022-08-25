#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <ui_core.h>
#include <OcularOS.h>
#include <OcularOS/WindowAPI.h>

int main(int argc, char** argv)
{
    char* dock_programs[12] = { "blank.elf", "0:/blank.tga", "term.elf", "0:/term.tga", "blank.elf", "0:/blank.tga", "blank.elf", "0:/blank.tga", "blank.elf", "0:/blank.tga", "blank.elf", "0:/blank.tga" };

    int x = 0, y = 0;
    Window window = create_window(1080, 70, "dock", false);
    int* framebuffer = get_framebuffer(window);
    window->y = 768-85;
    window->x = 0;

    terminal_initialize((uint32_t)framebuffer, 1080*sizeof(int), sizeof(int)*8, window->window_width, window->window_height);
    fillscreen(0x00000000);

    FILE img = fopen("0:/dock.tga", "r");
    struct file_stat stats;
    fstat(img, &stats);
    unsigned char* img_buf = malloc(stats.filesize);
    fread(img_buf, stats.filesize, 1, img);
    fclose(img);
    unsigned int* pix_data = tga_parse(img_buf, stats.filesize);
    draw_subbuffer(0, 0, pix_data[0], pix_data[1], (int*)(pix_data+2));

    for (int i = 0; i < (sizeof(dock_programs) / sizeof(char*)); i+=2)
    {
        img = fopen(dock_programs[i+1], "r");
        fstat(img, &stats);
        img_buf = malloc(stats.filesize);
        fread(img_buf, stats.filesize, 1, img);
        fclose(img);
        pix_data = tga_parse(img_buf, stats.filesize);
        draw_subbuffer((70*(i/2))+(10*(i/2))+40, 0, pix_data[0], pix_data[1], (int*)(pix_data+2));
    }

    terminal_putchar(0, 0, 'X', 0xffffffff);
    
    while (1)
    {
        window_update(window);
        int* temp = poll_mouse_move_event(window);
        if (temp != 0)
        {
            x = temp[0];
            y = temp[1];
        }
        if (poll_mouse_click_event(window) == 1)
        {
            for (int i = 0; i < (sizeof(dock_programs) / sizeof(char*)); i+=2)
            {
                if ((x >= (70*(i/2))+(10*(i/2))+40 && x <= (70*(i/2))+(10*(i/2))+40+70) && (y >= 0 && y <= window->window_height))
                {
                    system("1");
                    system(dock_programs[i]);
                }
            }
        }
    }

    window_shutdown(window);
    return 0;
}