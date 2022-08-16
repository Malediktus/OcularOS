#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOK_INT,
    TOK_FLOAT,
    TOK_IDENTIFIER,
    TOK_KEYWORD,
} token_type;

struct token
{
    token_type type;
    union
    {
        int int_value;
        float float_value;
        char* str_value;
    };
};

void visualize_token(struct token* token);

struct token* create_token(token_type type, void* value);
int delete_token(struct token* token);

int tokenize(struct token* out[], char* text);
int free_tokens(struct token** ptr);

#endif