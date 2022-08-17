#include "lexer.h"
#include "../config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int pow (int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if ((y % 2) == 0)
        return pow (x, y / 2) * pow (x, y / 2);
    else
        return x * pow (x, y / 2) * pow (x, y / 2);

}

Array* array_create()
{
    Array* result = malloc(sizeof(Array));
    result->data = malloc(sizeof(void*));
    result->size = 0;
    return result;
}

void array_free(Array* array)
{
    for (int i = 0; i < array->size; i++)
        free(array->data[i]);

    free(array->data);
    free(array);
}

void append(Array* array, void* element)
{
    array->size++;
    void* temp = malloc(sizeof(void*)*array->size);
    memcpy(temp, array->data, (array->size - 1)*sizeof(void*));
    free(array->data);
    array->data = temp;
    array->data[array->size-1] = element;
}

struct Token* token_create(enum token_type type, void* value, struct Position* pos_start, struct Position* pos_end)
{
    struct Token* result = malloc(sizeof(struct Token));
    result->type = type;
    result->pos_start = position_copy(pos_start);
    if (pos_end)
        result->pos_end = position_copy(pos_end);
    else
    {
        result->pos_end = position_copy(pos_start);
        position_advance(result->pos_end, 0);
    }
    switch (type)
    {
    case TT_INT:
        result->int_value = *((int*)value);
        free(value);
        break;
    case TT_FLOAT:
        result->float_value = *((float*)value);
        free(value);
        break;
    default:
        break;
    }

    return result;
}

void token_free(struct Token* token)
{
    position_free(token->pos_start);
    position_free(token->pos_end);
    free(token);
}

char* token_as_string(struct Token* token)
{
    char* result = malloc(SHELL_MAX_TOKEN_STRING_SIZE);
    switch (token->type)
    {
    case TT_INT:
        strcpy(result, "INT:");
        strcpy(result+strlen(result), itoa(token->int_value));
        break;
    case TT_FLOAT:
        strcpy(result, "FLOAT:~");
        strcpy(result+strlen(result), ftoa((double)token->float_value, 10));
        break;
    case TT_PLUS:
        strcpy(result, "PLUS");
        break;
    case TT_MINUS:
        strcpy(result, "MINUS");
        break;
    case TT_MUL:
        strcpy(result, "MUL");
        break;
    case TT_DIV:
        strcpy(result, "DIV");
        break;
    case TT_LPAREN:
        strcpy(result, "LPAREN");
        break;
    case TT_RPAREN:
        strcpy(result, "RPAREN");
        break;
    case TT_EOF:
        strcpy(result, "EOF");
        break;

    default:
        printf(itoa((int)token->type));
        strcpy(result, "Error");
        break;
    }

    return result;
}

void token_string_free(char* string)
{
    free(string);
}

struct Lexer* lexer_create(char* fn, char* text)
{
    struct Lexer* result = malloc(sizeof(struct Lexer));
    result->fn = fn;
    result->text = text;
    result->pos = position_create(-1, 0, -1, fn, text);
    result->current_char = 0x00;
    lexer_advance(result);
    return result;
}

void lexer_free(struct Lexer* lexer)
{
    position_free(lexer->pos);
    free(lexer);
}

void lexer_advance(struct Lexer* lexer)
{
    position_advance(lexer->pos, lexer->current_char);
    lexer->current_char = lexer->pos->idx < strlen(lexer->text) ? lexer->text[lexer->pos->idx] : 0x00;
}

void** lexer_make_tokens(struct Lexer* lexer)
{
    Array* tokens = array_create();

    while (lexer->current_char != 0x00)
    {
        if (lexer->current_char == ' ' || lexer->current_char == '\t')
            lexer_advance(lexer);
        else if (isdigit(lexer->current_char))
        {
            append(tokens, lexer_make_number(lexer));
        }
        else if (lexer->current_char == '+')
        {
            append(tokens, token_create(TT_PLUS, 0, lexer->pos, 0));
            lexer_advance(lexer);
        }
        else if (lexer->current_char == '-')
        {
            append(tokens, token_create(TT_MINUS, 0, lexer->pos, 0));
            lexer_advance(lexer);
        }
        else if (lexer->current_char == '*')
        {
            append(tokens, token_create(TT_MUL, 0, lexer->pos, 0));
            lexer_advance(lexer);
        }
        else if (lexer->current_char == '/')
        {
            append(tokens, token_create(TT_DIV, 0, lexer->pos, 0));
            lexer_advance(lexer);
        }
        else if (lexer->current_char == '(')
        {
            append(tokens, token_create(TT_LPAREN, 0, lexer->pos, 0));
            lexer_advance(lexer);
        }
        else if (lexer->current_char == ')')
        {
            append(tokens, token_create(TT_RPAREN, 0, lexer->pos, 0));
            lexer_advance(lexer);
        }
        else
        {
            struct Position* pos_start = position_copy(lexer->pos);
            char character = lexer->current_char;
            lexer_advance(lexer);
            char* details = malloc(3);
            details[0] = '\'';
            details[1] = character;
            details[2] = '\'';
            void** result = malloc(2*sizeof(void*));
            result[0] = 0x00;
            result[1] = error_create(pos_start, lexer->pos, ILLEGAL_CHAR_ERROR, details);
            return result;
        }
    }
    append(tokens, token_create(TT_EOF, 0, lexer->pos, 0));
    void** result = malloc(2*sizeof(void*));
    result[0] = tokens;
    result[1] = 0x00;
    return result;
}

struct Token* lexer_make_number(struct Lexer* lexer)
{
    float* result = malloc(sizeof(float));
    *result = 0;
    int dot_count = 0;
    int after_dot_count = 1;
    struct Position* pos_start = position_copy(lexer->pos);

    while (lexer->current_char != 0x00 && (isdigit(lexer->current_char) || lexer->current_char == '.'))
    {
        if (lexer->current_char == '.')
        {
            if (dot_count == 1) break;
            dot_count++;
        }
        else
        {
            if (dot_count == 0)
            {
                *result *= 10;
                *result += tonumericdigit(lexer->current_char);
            }
            else
            {
                *result *= pow(10, after_dot_count);
                *result += tonumericdigit(lexer->current_char);
                *result /= pow(10, after_dot_count);
                after_dot_count++;
            }
        }
        lexer_advance(lexer);
    }

    if (dot_count == 0)
    {
        int* temp = malloc(sizeof(int));
        *temp = (int)*result;
        free(result);
        struct Token* res = token_create(TT_INT, temp, pos_start, lexer->pos);
        position_free(pos_start);
        return res;
    }
    struct Token* res = token_create(TT_FLOAT, result, pos_start, lexer->pos);
    position_free(pos_start);
    return res;
}

void token_list_free(void** list)
{
    if (list[0] == 0x00)
    {
        struct Error* err = (struct Error*)list[1];
        free(err->details);
        error_free(err);
    }
    else
    {
        array_free((Array*)list[0]);
    }
    free(list);
}