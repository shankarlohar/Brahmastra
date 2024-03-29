#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

/* Declare a buffer for user of input size 2048 */
static char input[2048];

int main(int arg, char **argv)
{
    /* Print Version and Exit Information */
    puts("Lisp Version 0.0.1");
    puts("Press Ctr+c to Exit\n");

    /* In a never ending loop */
    while (1)
    {
        /* Output our promp and get input */
        char *input = readline("Lispy> ");

        /* Add input to history */
        add_history(input);

        /* Echo input back to the user */

        printf("No you're a %s\n", input);

        /* Free retrieved input */
        free(input);
    }

    return 0;
}