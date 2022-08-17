#include "error.h"
#include "../config.h"
#include <string.h>
#include <stdlib.h>
#include <memory.h>

struct Position* position_create(int idx, int ln, int col, char* fn, char* ftxt)
{
    struct Position* result = malloc(sizeof(struct Position));
    result->idx = idx;
    result->ln = ln;
    result->col = col;
    result->fn = fn;
    result->ftxt = ftxt;
    return result;
}

void position_free(struct Position* position)
{
    free(position);
}

struct Position* position_advance(struct Position* position, char current_char)
{
    position->idx++;
    position->col++;

    if (current_char == '\n')
    {
        position->ln++;
        position->col++;
    }

    return position;
}

struct Position* position_copy(struct Position* position)
{
    struct Position* result = malloc(sizeof(struct Position));
    memcpy(result, position, sizeof(struct Position));
    return result;
}

struct Error* error_create(struct Position* pos_start, struct Position* pos_end, enum Errors type, char* details)
{
    struct Error* result = malloc(sizeof(struct Error));
    result->pos_start = pos_start;
    result->pos_end = pos_end;
    result->error_type = type;
    result->details = details;
    return result;
}

void error_free(struct Error* error)
{
    free(error);
}

char* error_as_string(struct Error* error)
{
    char* result = malloc(SHELL_MAX_ERROR_SIZE);
    switch (error->error_type)
    {
    case ILLEGAL_CHAR_ERROR:
        strcpy(result, "Illegal Character: ");
        break;
    case INVALID_SYNTAX_ERROR:
        strcpy(result, "Invalid Syntax: ");
        break;
    case RUNTIME_ERROR:
        strcpy(result, "Runtime Error: ");
        break;
    }

    strcpy(result+strlen(result), error->details);
    strcpy(result+strlen(result), "\nFile ");
    strcpy(result+strlen(result), error->pos_start->fn);
    strcpy(result+strlen(result), ", line ");
    strcpy(result+strlen(result), itoa(error->pos_start->ln+1));

    return result;
}

void error_string_free(char* string)
{
    free(string);
}

char* string_with_arrows(char* text, struct Position* pos_start, struct Position* pos_end)
{
    return "Not yet implemented";
}