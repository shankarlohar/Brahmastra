#include <stdio.h>
#include <stdlib.h>

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
    /* Print Version and Exit Information */
    puts("Maya Version 0.0.1");
    puts("Press Ctr+c to Exit\n");

    /* In a never ending loop */
    while (1)
    {
        /* Output our promp and get input */
        char *input = readline("Maya> ");

        /* Add input to history */
        add_history(input);

        /* Echo input back to the user */

        printf("No you're a %s\n", input);

        /* Free retrieved input */
        free(input);
    }

    return 0;
}