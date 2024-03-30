#include "mpc.h"

/* If we are compiling on windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline funciton */
char *readline(char *propt)
{
    fputs(promp, stdout);
    fgets(buffer, 2048, stdin);
    char *cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

/* Fake add_history function */
void add_history(char *unused) {}

/* Otherwise use the editline header */
#else
#include <editline/readline.h>
#endif

/* Declare a buffer for user of input size 2048 */
static char input[2048];

int main(int arg, char **argv)
{

    /* Create Some Parser */

    mpc_parser_t *Number = mpc_new("number");
    mpc_parser_t *Operator = mpc_new("operator");
    mpc_parser_t *Expr = mpc_new("expr");
    mpc_parser_t *Lispy = mpc_new("lispy");

    /* Define them with the following Language */

    mpca_lang(MPCA_LANG_DEFAULT,
              "                                                     \
    number   : /-?[0-9]+/ ;                             \
    operator : '+' | '-' | '*' | '/' ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;  \
    lispy    : /^/ <operator> <expr>+ /$/ ;             \
  ",
              Number, Operator, Expr, Lispy);

    /* Print Version and Exit Information */
    puts("Brahmastra Version 0.0.1");
    puts("Press Ctr+c to Exit\n");

    /* In a never ending loop */
    while (1)
    {
        /* Output our promp and get input */
        char *input = readline("Brahmastra> ");

        /* Add input to history */
        add_history(input);

        /* Attempts to parse the user input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r))
        {
            /* On Success Pring the AST */
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        }
        else
        {
            /* Otherwise Print the Error*/
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
    }

    /* Undefine and delete our parsers */
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}