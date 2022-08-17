#ifndef LEXER_H
#define LEXER_H

#include "error.h"
#include <memory.h>

enum token_type
{
    TT_INT,
    TT_FLOAT,
    TT_PLUS,
    TT_MINUS,
    TT_MUL,
    TT_DIV,
    TT_LPAREN,
    TT_RPAREN,
    TT_EOF,
};

struct Token
{
    enum token_type type;
    struct Position* pos_start;
    struct Position* pos_end;
    union
    {
        int int_value;
        float float_value;
        char* str_value;
    };
};

struct Lexer
{
    char* fn;
    char* text;
    struct Position* pos;
    char current_char;
};

typedef struct
{
    void** data;
    unsigned int size;
} Array;

Array* array_create();
void array_free(Array* array);
void append(Array* array, void* element);

struct Token* token_create(enum token_type type, void* value, struct Position* pos_start, struct Position* pos_end);
void token_free(struct Token* token);
char* token_as_string(struct Token* token);
void token_string_free(char* string);

struct Lexer* lexer_create(char* fn, char* text);
void lexer_free(struct Lexer* lexer);
void lexer_advance(struct Lexer* lexer);
void** lexer_make_tokens(struct Lexer* lexer);
struct Token* lexer_make_number(struct Lexer* lexer);

void token_list_free(void** list);

#endif