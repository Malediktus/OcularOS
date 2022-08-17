#ifndef ERROR_H
#define ERROR_H

enum Errors
{
    ILLEGAL_CHAR_ERROR,
    INVALID_SYNTAX_ERROR,
    RUNTIME_ERROR,
};

struct Position
{
    int idx;
    int ln;
    int col;
    char* fn;
    char* ftxt;
};

struct Error
{
    struct Position* pos_start;
    struct Position* pos_end;
    enum Errors error_type;
    char* details;
};

struct Position* position_create(int idx, int ln, int col, char* fn, char* ftxt);
void position_free(struct Position* position);
struct Position* position_advance(struct Position* position, char current_char);
struct Position* position_copy(struct Position* position);

struct Error* error_create(struct Position* pos_start, struct Position* pos_end, enum Errors type, char* details);
void error_free(struct Error* error);
char* error_as_string(struct Error* error);
void error_string_free(char* string);

char* string_with_arrows(char* text, struct Position* pos_start, struct Position* pos_end);

#endif