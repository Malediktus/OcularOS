#include "interpreter/lexer.h"
#include "interpreter/parser.h"
#include "interpreter/interpreter.h"
#include "shell.h"
#include "config.h"
#include <OcularOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RTResult run(char* fn, char* text)
{
    struct RTResult temp = rt_result_create();
    // Generate tokens
    struct Lexer* lexer = lexer_create(fn, text);
    void** lex_result = lexer_make_tokens(lexer);
    struct Token** tokens = (struct Token**)((Array*)lex_result[0])->data;
    struct Error* error = (struct Error*)lex_result[1];
    if (error)
    {
        return rt_result_failure(&temp, error);
    }

    // Generate AST
    struct Parser* parser = parser_create(tokens, ((Array*)lex_result[0])->size);
    struct ParseResult ast = parser_parse(parser);
    if (ast.error != 0)
    {
        return rt_result_failure(&temp, ast.error);
    }

    // Evaluate command
    struct RTResult result = interpreter_visit(ast.node);
    return result;
}

int main(int argc, char** argv)
{
    // TODO: allow arguments to use quotes
    char* terminal_ipc = ocularos_start_ipc("term.elf", SHELL_MAX_INPUT_SIZE+(1080/8)*(768/8));
    if (terminal_ipc == 0)
        print("OcularOS v1.0.0\n");
    else
        strcpy(terminal_ipc, "OcularOS v1.0.0\n");
    while (1)
    {
        print("> ");
        char buf[SHELL_MAX_INPUT_SIZE];
        ocularos_readline(buf, sizeof(buf), true);
        print("\n");

        char buf_lower[4];
        for (int i = 0; i < 4; i++)
            buf_lower[i] = tolower(buf[i]);

        if (strncmp(buf_lower, "exit", 4) == 0) exit(0);

        int code = system(buf);
        if (code < 0)
        {
            struct RTResult result = run("<stdin>", buf);
            if (result.error)
            {
                if (result.error->error_type == ILLEGAL_CHAR_ERROR)
                {
                    printf("Command '%s' not found\n", buf);
                }
                else
                {
                    printf("%s\n", error_as_string(result.error));
                }
            }
            else
                printf("%s\n", number_as_string(result.value));
        }
        ocularos_free_all();
        asm("int $0x80" : : "a" (23));
    }

    return 0;
}