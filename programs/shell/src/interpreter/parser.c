#include "parser.h"
#include <stdio.h>

struct ParseResult parser_parse(struct Parser* parser)
{
    struct ParseResult res = parser_expr(parser);
    if (res.error == 0 && parser->current_tok->type != TT_EOF)
    {
        return parse_result_failure(&res, error_create(parser->current_tok->pos_start, parser->current_tok->pos_end, INVALID_SYNTAX_ERROR, "Expected '+', '-', '*' or '/'")); // TODO: Remember to free the error
    }
    return res;
}

struct ParseResult parser_factor(struct Parser* parser)
{
    struct ParseResult res = parse_result_create();
    struct Token* tok = parser->current_tok;
    if (tok->type == TT_PLUS || tok->type == TT_MINUS)
    {
        parse_result_register_advance(&res, parser_advance(parser));
        struct Node* factor = parse_result_register(&res, parser_factor(parser));
        if (res.error != 0) return res;
        return parse_result_success(&res, node_create(UNARY_OP_NODE, unary_op_node_create(tok, factor)));
    }
    else if (tok->type == TT_INT || tok->type == TT_FLOAT)
    {
        parse_result_register_advance(&res, parser_advance(parser));
        return parse_result_success(&res, node_create(NUMBER_NODE, number_node_create(tok)));
    }
    else if (tok->type == TT_LPAREN)
    {
        parse_result_register_advance(&res, parser_advance(parser));
        struct Node* expr = parse_result_register(&res, parser_expr(parser));
        if (res.error != 0) return res;
        if (parser->current_tok->type == TT_RPAREN)
        {
            parse_result_register_advance(&res, parser_advance(parser));
            return parse_result_success(&res, expr);
        }
        else
        {
            return parse_result_failure(&res, error_create(parser->current_tok->pos_start, parser->current_tok->pos_end, INVALID_SYNTAX_ERROR, "Expected ')'"));
        }
    }
    return parse_result_failure(&res, error_create(tok->pos_start, tok->pos_end, INVALID_SYNTAX_ERROR, "Expected int or float"));
}

struct ParseResult parser_term(struct Parser* parser)
{
    return parser_bin_op(parser, parser_factor, TT_MUL, TT_DIV);
}

struct ParseResult parser_expr(struct Parser* parser)
{
    return parser_bin_op(parser, parser_term, TT_PLUS, TT_MINUS);
}

struct ParseResult parser_bin_op(struct Parser* parser, struct ParseResult (*func)(struct Parser*), enum token_type op1, enum token_type op2)
{
    struct ParseResult res = parse_result_create();
    struct Node* left = parse_result_register(&res, func(parser));
    if (res.error != 0) return res;

    while (parser->current_tok->type == op1 || parser->current_tok->type == op2)
    {
        struct Token* op_tok = parser->current_tok;
        parse_result_register_advance(&res, parser_advance(parser));
        struct Node* right = parse_result_register(&res, func(parser));
        if (res.error != 0) return res;
        left = node_create(BIN_OP_NODE, bin_op_node_create(left, op_tok, right));
    }

    return parse_result_success(&res, left);
}