#include "lexer.h"
#include "../config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void visualize_token(struct token* token)
{
    switch (token->type)
    {
        case TOK_INT:
            printf("INT:");
            printf("%i\n", token->int_value);
            break;
        case TOK_FLOAT:
            printf("FLOAT:");
            //printf("%d\n", token->float_value); we dont support %d yet
            break;
        case TOK_IDENTIFIER:
            printf("IDENTIFIER:");
            printf("%s\n", token->str_value);
            break;
        case TOK_KEYWORD:
            printf("KEYWORD:");
            printf("%s\n", token->str_value);
            break;
        default:
            printf("Unknow token\n");
    }
}

struct token* create_token(token_type type, void* value)
{
    struct token* result = malloc(sizeof(struct token));
    result->type = type;
    switch (type)
    {
    case TOK_INT:
        result->int_value = *((int*)value);
    case TOK_FLOAT:
        result->float_value = *((float*)value);
    case TOK_IDENTIFIER:
        result->str_value = malloc(SHELL_MAX_INPUT_SIZE);
        strcpy(result->str_value, value);
    case TOK_KEYWORD:
        result->str_value = malloc(SHELL_MAX_INPUT_SIZE);
        strcpy(result->str_value, value);
    }

    return result;
}

int delete_token(struct token* token)
{
    if (token->type == TOK_IDENTIFIER || token->type == TOK_KEYWORD)
        free(token->str_value);
    free(token);
    return 0;
}

int tokenize(struct token* out[], char* text)
{
    return 0;
}

int free_tokens(struct token** ptr)
{
    for (int i = 0; i < SHELL_MAX_TOKENS; i++)
        if (ptr[i])
            delete_token(ptr[i]);

    return 0;
}