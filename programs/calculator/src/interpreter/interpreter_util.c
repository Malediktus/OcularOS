#include "interpreter.h"
#include "error.h"
#include "../config.h"
#include <stdlib.h>

struct RTResult rt_result_create()
{
    struct RTResult result;
    result.error = 0;
    result.value = 0;
    return result;
}

void* rt_result_register(struct RTResult* rt_result, struct RTResult res)
{
    if (res.error) rt_result->error = res.error;
    return res.value;
}

struct RTResult rt_result_success(struct RTResult* rt_result, void* value)
{
    rt_result->value = value;
    return *rt_result;
}

struct RTResult rt_result_failure(struct RTResult* rt_result, struct Error* error)
{
    rt_result->error = error;
    return *rt_result;
}

struct Number* number_create(float value)
{
    struct Number* result = malloc(sizeof(struct Number));
    result->value = value;
    result->pos_start = 0;
    result->pos_end = 0;
    return result;
}

void number_free(struct Number* number)
{
    free(number);
}

struct Number* number_set_pos(struct Number* number, struct Position* pos_start, struct Position* pos_end)
{
    number->pos_start = pos_start;
    number->pos_end = pos_end;
    return number;
}

struct RTResult number_added_to(struct Number* number, struct Number* other)
{
    struct RTResult res = rt_result_create();
    float* temp = malloc(sizeof(float));
    *temp = number->value + other->value;
    return rt_result_success(&res, temp);
}

struct RTResult number_subbed_by(struct Number* number, struct Number* other)
{
    struct RTResult res = rt_result_create();
    float* temp = malloc(sizeof(float));
    *temp = number->value - other->value;
    return rt_result_success(&res, temp);
}

struct RTResult number_multed_by(struct Number* number, struct Number* other)
{
    struct RTResult res = rt_result_create();
    float* temp = malloc(sizeof(float));
    *temp = number->value * other->value;
    return rt_result_success(&res, temp);
}

struct RTResult number_dived_by(struct Number* number, struct Number* other)
{
    struct RTResult res = rt_result_create();
    if (other->value == 0)
        return rt_result_failure(&res, error_create(other->pos_start, other->pos_end, RUNTIME_ERROR, "Division by zero"));
    float* temp = malloc(sizeof(float));
    *temp = number->value / other->value;
    return rt_result_success(&res, temp);
}

char* number_as_string(struct Number* number)
{
    return itoa(number->value);
}