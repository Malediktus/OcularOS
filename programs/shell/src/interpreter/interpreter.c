#include "interpreter.h"

struct RTResult interpreter_visit(struct Node* node)
{
    switch (node->type)
    {
    case NUMBER_NODE:
        return interpreter_visit_NumberNode(node);
        break;
    case BIN_OP_NODE:
        return interpreter_visit_BinOpNode(node);
        break;
    case UNARY_OP_NODE:
        return interpreter_visit_UnaryOpNode(node);
        break;
    }
    return rt_result_create();
}

struct RTResult interpreter_visit_NumberNode(struct Node* node)
{
    struct RTResult res = rt_result_create();
    struct Number* number = number_create(node->number_node_value->tok->type == TT_INT ? (float)node->number_node_value->tok->int_value : node->number_node_value->tok->float_value);
    number_set_pos(number, node->pos_start, node->pos_end);
    return rt_result_success(&res, number);
}

struct RTResult interpreter_visit_BinOpNode(struct Node* node)
{
    struct RTResult res = rt_result_create();
    struct Number* left = (struct Number*)rt_result_register(&res, interpreter_visit(node->bin_op_node_value->left_node));
    if (res.error) return res;
    struct Number* right = (struct Number*)rt_result_register(&res, interpreter_visit(node->bin_op_node_value->right_node));
    if (res.error) return res;

    switch (node->bin_op_node_value->op_tok->type)
    {
    case TT_PLUS:
        res = number_added_to(left, right);
        break;
    case TT_MINUS:
        res = number_subbed_by(left, right);
        break;
    case TT_MUL:
        res = number_multed_by(left, right);
        break;
    case TT_DIV:
        res = number_dived_by(left, right);
        break;
    default:
        break;
    }

    if (res.error) return res;
    number_set_pos(res.value, node->pos_start, node->pos_end);
    return res;
}

struct RTResult interpreter_visit_UnaryOpNode(struct Node* node)
{
    struct RTResult res = rt_result_create();
    struct Number* number = (struct Number*)rt_result_register(&res, interpreter_visit(node->unary_op_node_value->node));
    if (res.error) return res;

    if (node->unary_op_node_value->op_tok->type == TT_MINUS)
        res = number_multed_by(number, number_create(-1));

    if (res.error) return res;
    number_set_pos(res.value, node->pos_start, node->pos_end);
    return res;
}