#include "argument.h"
#include <string.h>
#include <stdlib.h>

struct command_argument* parse_command(const char* command, int max)
{
    struct command_argument* root_command = 0;
    char scommand[1024];
    if (max >= (int)sizeof(scommand))
        return max;
    
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
    }
}