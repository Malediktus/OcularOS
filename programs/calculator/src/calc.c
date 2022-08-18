#include "interpreter/lexer.h"
#include "interpreter/parser.h"
#include "interpreter/interpreter.h"
#include "config.h"
#include <OcularOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void** run(char* fn, char* text)
{
    // Generate tokens
    struct Lexer* lexer = lexer_create(fn, text);
    void** lex_result = lexer_make_tokens(lexer);
    struct Token** tokens = (struct Token**)((Array*)lex_result[0])->data;
    struct Error* error = (struct Error*)lex_result[1];
    if (error)
    {
        printf("%s\n", error_as_string(error));
        return 0;
    }

    // Generate AST
    struct Parser* parser = parser_create(tokens, ((Array*)lex_result[0])->size);
    struct ParseResult ast = parser_parse(parser);
    if (ast.error != 0)
    {
        printf("%s\n", error_as_string(ast.error));
        return 0;
    }

    // Evaluate command
    struct RTResult result = interpreter_visit(ast.node);

    if (result.error)
    {
        printf("%s\n", error_as_string(result.error));
        return 0;
    }
    printf("%s\n", number_as_string(result.value));

    return 0;
}

int main(int argc, char** argv)
{
    print("Calculator v1.0.0\n");
    while (1)
    {
        print("Enter equation >> ");
        char buf[CALC_MAX_INPUT_SIZE];
        ocularos_readline(buf, sizeof(buf), true);
        print("\n");

        char buf_lower[4];
        for (int i = 0; i < 4; i++)
            buf_lower[i] = tolower(buf[i]);

        if (strncmp(buf_lower, "exit", 4) == 0) exit(0);

        run("<stdin>", buf);

        ocularos_free_all();
    }

    return 0;
}