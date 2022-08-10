#include <lib/screen.h>

void terminal_putchar(int x, int y, char c, char colour);
void terminal_writechar(char c, char colour);

uint16_t* video_memory = 0;

void terminal_initialize()
{
    video_memory = (uint16_t*)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}

void print(string str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

////////////////////////////////////////////////////////////////////////
////// PRIVATE API /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void terminal_writechar(char c, char colour)
{
    static uint16_t terminal_row = 0, terminal_col = 0;

    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }
    
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_memory[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}