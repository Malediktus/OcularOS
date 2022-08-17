#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

struct RTResult
{
    struct Error* error;
    void* value;
};

struct RTResult rt_result_create();
void* rt_result_register(struct RTResult* rt_result, struct RTResult res);
struct RTResult rt_result_success(struct RTResult* rt_result, void* value);
struct RTResult rt_result_failure(struct RTResult* rt_result, struct Error* error);

struct Number
{
    float value;
    struct Position* pos_start;
    struct Position* pos_end;
};

struct Number* number_create(float value);
void number_free(struct Number* number);
struct Number* number_set_pos(struct Number* number, struct Position* pos_start, struct Position* pos_end);
struct RTResult number_added_to(struct Number* number, struct Number* other);
struct RTResult number_subbed_by(struct Number* number, struct Number* other);
struct RTResult number_multed_by(struct Number* number, struct Number* other);
struct RTResult number_dived_by(struct Number* number, struct Number* other);
char* number_as_string(struct Number* number);

struct RTResult interpreter_visit(struct Node* node);
struct RTResult interpreter_visit_NumberNode(struct Node* node);
struct RTResult interpreter_visit_BinOpNode(struct Node* node);
struct RTResult interpreter_visit_UnaryOpNode(struct Node* node);

#endif