#include "stdlib.h"
#include "string.h"
#include "OcularOS.h"

void* ocularos_malloc(size_t size);
void ocularos_free(void* ptr);

void* malloc(size_t size)
{
    return ocularos_malloc(size);
}

void free(void* ptr)
{
    ocularos_free(ptr);
}

char* itoa(int i)
{
    static char text[12];
    int loc = 11;
    text[11] = 0;
    char neg = 1;
    if (i >= 0)
    {
        neg = 0;
        i = -i;
    }

    while (i)
    {
        text[--loc] = '0' - (i % 10);
        i /= 10;
    }

    if (loc == 11)
        text[--loc] = '0';

    if (neg)
        text[--loc] = '-';
    
    return &text[loc];
}

struct command_argument* _parse_command(const char* command, int max)
{
    struct command_argument* root_command = 0;
    char scommand[1025];
    if (max >= (int)sizeof(scommand))
        return 0;
    
    strncpy(scommand, command, sizeof(scommand));
    char* token = strtok(scommand, " ");
    if (!token)
        return root_command;
    
    root_command = malloc(sizeof(struct command_argument));
    if (!root_command)
        return root_command;

    strncpy(root_command->argument, token, sizeof(root_command->argument));
    root_command->next = 0;

    struct command_argument* current = root_command;
    token = strtok(NULL, " ");
    while (token != 0)
    {
        struct command_argument* new_command = malloc(sizeof(struct command_argument));
        if (!new_command)
            break;
        
        strncpy(new_command->argument, token, sizeof(new_command->argument));
        new_command->next = 0x00;
        current->next = new_command;
        current = new_command;
        token = strtok(NULL, " ");
    }

    return root_command;
}

int system(const char *command)
{
    char buf[1024];
    strncpy(buf, command, sizeof(buf));
    struct command_argument* root_command_argument = _parse_command(buf, sizeof(buf));
    if (!root_command_argument)
        return -1;

    return ocularos_system(root_command_argument);
}