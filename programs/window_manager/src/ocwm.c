#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <OcularOS.h>
#include "backend/sysfunction.h"

int rgb_to_hex(int r, int b, int g)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int main(int argc, char** argv)
{
    /*FILE wallpaper = fopen("0:/img.ppm", "r");
    if (!wallpaper)
    {
        printf("Couldnt load img.ppm\n");
        exit(1);
    }

    struct file_stat stats;
    if(fstat(wallpaper, &stats) < 0)
    {
        printf("Couldnt stat img.ppm\n");
        exit(1);
    }
    int start = stats.filesize - (1024 * 768 * 3);
    char* data = malloc(1024 * 768 * 3);

    if(fseek(wallpaper, start, SEEK_SET) < 0)
    {
        printf("Couldnt seek img.ppm\n");
        exit(1);
    }

    for (int i = 0; i < 768; i++)
    {
    int status = fread(data+(i*1024*3), 1024 * 3, 1, wallpaper);
    if(status < 0)
    {
        printf("Couldnt read img.ppm. Error code: %i\n", status);
        exit(1);
    }
    if(fseek(wallpaper, 1024 * 3, SEEK_CUR) < 0)
    {
        printf("Couldnt seek img.ppm\n");
        exit(1);
    }
    }

    int i = 0;
    for (int y = 0; y < 768; y++)
    {
        if(fseek(wallpaper, start+(y*1024*3), SEEK_SET) < 0)
        {
            printf("Couldnt seek img.ppm\n");
            exit(1);
        }
        int status = fread(data, 1024 * 3, 1, wallpaper);
        if(status < 0)
        {
            printf("Couldnt read img.ppm. Error code: %i\n", status);
            exit(1);
        }

        for (int x = 0; x < 1024; x++)
        {
            putpixel(x, y, rgb_to_hex(data[i], data[i+1], data[i+2]));
            i += 3;
        }
    }
    
    fclose(wallpaper);*/

    void* ptr = ocularos_start_ipc("0:/usr/bin/blank.elf", 512);
    if (!ptr)
        print("Error");
    while (1);
    return 0;
}