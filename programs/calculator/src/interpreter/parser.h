#ifndef PARSER_H
#define PARSER_H

#include "error.h"
#include "lexer.h"
#include "../config.h"
#include <stdlib.h>
#include <string.h>

enum node_type
{
    NUMBER_NODE,
    BIN_OP_NODE,
    UNARY_OP_NODE,
};

struct NumberNode
{
    struct Token* tok;
};

struct NumberNode* number_node_create(struct Token* tok);
void number_node_free(struct NumberNode* node);
char* number_node_as_string(struct NumberNode* node);
void number_node_string_free(char* string);

struct BinOpNode
{
    struct Node* left_node;
    struct Token* op_tok;
    struct Node* right_node;
};

struct BinOpNode* bin_op_node_create(struct Node* left_node, struct Token* op_tok, struct Node* right_node);
void bin_op_node_free(struct BinOpNode* node);
char* bin_op_node_as_string(struct BinOpNode* node);
void bin_op_node_string_free(char* str);

struct UnaryOpNode
{
    struct Token* op_tok;
    struct Node* node;
};

struct UnaryOpNode* unary_op_node_create(struct Token* op_tok, struct Node* node);
void unary_op_node_free(struct UnaryOpNode* node);
char* unary_op_node_as_string(struct UnaryOpNode* node);
void unary_op_node_string_free(char* str);

struct Node
{
    enum node_type type;
    union
    {
        struct NumberNode* number_node_value;
        struct BinOpNode* bin_op_node_value;
        struct UnaryOpNode* unary_op_node_value;
    };
    struct Position* pos_start;
    struct Position* pos_end;
};

struct Node* node_create(enum node_type type, void* value);
void node_free(struct Node* node);
char* node_as_string(struct Node* node);
void node_string_free(struct Node* node, char* str);

struct ParseResult
{
    struct Error* error;
    struct Node* node;
};

struct ParseResult parse_result_create();
struct Node* parse_result_register(struct ParseResult* parse_result, struct ParseResult res);
struct Token* parse_result_register_advance(struct ParseResult* parse_result, struct Token* res);
struct ParseResult parse_result_success(struct ParseResult* parse_result, struct Node* node);
struct ParseResult parse_result_failure(struct ParseResult* parse_result, struct Error* error);

struct Parser
{
    struct Token** tokens;
    int tokens_size;
    int tok_idx;
    struct Token* current_tok;
};

struct Parser* parser_create(struct Token** tokens, int tokens_size);
void parser_free(struct Parser* parser);
struct Token* parser_advance(struct Parser* parser);

struct ParseResult parser_parse(struct Parser* parser);
struct ParseResult parser_factor(struct Parser* parser);
struct ParseResult parser_expr(struct Parser* parser);
struct ParseResult parser_term(struct Parser* parser);
struct ParseResult parser_bin_op(struct Parser* parser, struct ParseResult (*func)(struct Parser*), enum token_type op1, enum token_type op2);

#endif