#include "parser.h"

struct NumberNode* number_node_create(struct Token* tok)
{
    struct NumberNode* result = malloc(sizeof(struct NumberNode));
    result->tok = tok;
    return result;
}

void number_node_free(struct NumberNode* node)
{
    free(node);
}

char* number_node_as_string(struct NumberNode* node)
{
    char* result = malloc(CALC_MAX_NODE_STRING_SIZE);
    strcpy(result, "(");

    char* temp = token_as_string(node->tok);
    strcpy(result+strlen(result), temp);
    token_string_free(temp);

    strcpy(result+strlen(result), ")");

    return result;
}

void number_node_string_free(char* string)
{
    free(string);
}

struct BinOpNode* bin_op_node_create(struct Node* left_node, struct Token* op_tok, struct Node* right_node)
{
    struct BinOpNode* result = malloc(sizeof(struct BinOpNode));
    result->left_node = left_node;
    result->op_tok = op_tok;
    result->right_node = right_node;
    return result;
}

void bin_op_node_free(struct BinOpNode* node)
{
    free(node);
}

char* bin_op_node_as_string(struct BinOpNode* node)
{
    char* result = malloc(CALC_MAX_NODE_STRING_SIZE);
    strcpy(result, "(");

    char* temp = node_as_string(node->left_node);
    strcpy(result+strlen(result), temp);
    node_string_free(node->left_node, temp);

    strcpy(result+strlen(result), ", ");

    char* temp2 = token_as_string(node->op_tok);
    strcpy(result+strlen(result), temp2);
    token_string_free(temp2);

    strcpy(result+strlen(result), ", ");

    char* temp3 = node_as_string(node->right_node);
    strcpy(result+strlen(result), temp3);
    node_string_free(node->right_node, temp3);

    strcpy(result+strlen(result), ")");
    return result;
}

void bin_op_node_string_free(char* str)
{
    free(str);
}

struct UnaryOpNode* unary_op_node_create(struct Token* op_tok, struct Node* node)
{
    struct UnaryOpNode* result = malloc(sizeof(struct UnaryOpNode));
    result->op_tok = op_tok;
    result->node = node;
    return result;
}

void unary_op_node_free(struct UnaryOpNode* node)
{
    free(node);
}

char* unary_op_node_as_string(struct UnaryOpNode* node)
{
    char* result = malloc(CALC_MAX_NODE_STRING_SIZE);
    strcpy(result, "(");

    char* temp = token_as_string(node->op_tok);
    strcpy(result+strlen(result), temp);
    token_string_free(temp);

    strcpy(result+strlen(result), ", ");

    char* temp2 = node_as_string(node->node);
    strcpy(result+strlen(result), temp2);
    node_string_free(node->node, temp2);

    strcpy(result+strlen(result), ")");
    return result;
}

void unary_op_node_string_free(char* str)
{
    free(str);
}

struct Node* node_create(enum node_type type, void* value)
{
    struct Node* result = malloc(sizeof(struct Node));
    result->type = type;

    switch (type)
    {
    case NUMBER_NODE:
        result->number_node_value = value;
        result->pos_start = result->number_node_value->tok->pos_start;
        result->pos_end = result->number_node_value->tok->pos_end;
        break;
    case BIN_OP_NODE:
        result->bin_op_node_value = value;
        result->pos_start = result->bin_op_node_value->left_node->pos_start;
        result->pos_end = result->bin_op_node_value->right_node->pos_end;
        break;
    case UNARY_OP_NODE:
        result->unary_op_node_value = value;
        result->pos_start = result->unary_op_node_value->op_tok->pos_start;
        result->pos_end = result->unary_op_node_value->node->pos_end;
        break;
    }

    return result;
}

void node_free(struct Node* node)
{
    free(node);
    switch (node->type)
    {
    case NUMBER_NODE:
        number_node_free(node->number_node_value);
        position_free(node->pos_start);
        position_free(node->pos_end);
        break;
    case BIN_OP_NODE:
        bin_op_node_free(node->bin_op_node_value);
        position_free(node->pos_start);
        position_free(node->pos_end);
        break;
    case UNARY_OP_NODE:
        unary_op_node_free(node->unary_op_node_value);
        position_free(node->pos_start);
        position_free(node->pos_end);
        break;
    }
}

char* node_as_string(struct Node* node)
{
    switch (node->type)
    {
    case NUMBER_NODE:
        return number_node_as_string(node->number_node_value);
        break;
    case BIN_OP_NODE:
        return bin_op_node_as_string(node->bin_op_node_value);
        break;
    case UNARY_OP_NODE:
        return unary_op_node_as_string(node->unary_op_node_value);
        break;
    default:
        return 0;
    }
}

void node_string_free(struct Node* node, char* str)
{
    switch (node->type)
    {
    case NUMBER_NODE:
        number_node_string_free(str);
        break;
    case BIN_OP_NODE:
        bin_op_node_string_free(str);
        break;
    case UNARY_OP_NODE:
        unary_op_node_string_free(str);
        break;
    }
}

struct ParseResult parse_result_create()
{
    struct ParseResult result;
    result.error = 0;
    result.node = 0;
    return result;
}

struct Node* parse_result_register(struct ParseResult* parse_result, struct ParseResult res)
{
    if (res.error)
        parse_result->error = res.error;
    return res.node;
}

struct Token* parse_result_register_advance(struct ParseResult* parse_result, struct Token* res)
{
    return res;
}

struct ParseResult parse_result_success(struct ParseResult* parse_result, struct Node* node)
{
    parse_result->node = node;
    return *parse_result;
}

struct ParseResult parse_result_failure(struct ParseResult* parse_result, struct Error* error)
{
    parse_result->error = error;
    return *parse_result;
}

struct Parser* parser_create(struct Token** tokens, int tokens_size)
{
    struct Parser* result = malloc(sizeof(struct Parser));
    result->tokens = tokens;
    result->tokens_size = tokens_size;
    result->tok_idx = -1;
    result->current_tok = 0x00;
    parser_advance(result);
    return result;
}

void parser_free(struct Parser* parser)
{
    free(parser);
}

struct Token* parser_advance(struct Parser* parser)
{
    parser->tok_idx++;
    if (parser->tok_idx < parser->tokens_size)
        parser->current_tok = parser->tokens[parser->tok_idx];
    return parser->current_tok;
}