#ifndef ARGUMENT_H
#define ARGUMENT_H

struct command_argument
{
    char argument[512];
    struct command_argument* next;
};

#endif