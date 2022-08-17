#include "interpreter/lexer.h"
#include "interpreter/parser.h"
#include "interpreter/interpreter.h"
#include "shell.h"
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
    // TODO: allow arguments to use quotes
    print("OcularOS v1.0.0\n");
    while (1)
    {
        print("> ");
        char buf[SHELL_MAX_INPUT_SIZE];
        ocularos_readline(buf, sizeof(buf), true);
        print("\n");

        // TODO: Check for keywords/number
        run("<stdin>", buf);

        int code = system(buf);
        if (code < 0)
            printf("Command '%s' not found\n", buf);

        /*if (result[1] != 0x00)
        {
            struct Error* error = (struct Error*)result[1];
            char* str = error_as_string(error);
            printf("%s\n", str);
            error_string_free(str);
        }
        else
        {
            struct Token** tokens = (struct Token**)((Array*)result[0])->data;
            for (int i = 0; i < ((Array*)result[0])->size; i++)
            {
                char* str = token_as_string(tokens[i]);
                printf("%s\n", str);
                token_string_free(str);
            }
        }

        token_list_free(result);*/

        ocularos_free_all();
    }

    return 0;
}