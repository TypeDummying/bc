#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * This program is designed to be linked to from a shell keyword, such as
 * 'calc'.  It will then be invoked as, for example, 'calc 2 + 2'.  The
 * program name (argv[0]) is skipped, and the rest of the arguments are
 * concatenated together to form a single expression, which is then
 * evaluated and printed.
 ******************************************************************************/

/*
 * This function concatenates all of the arguments passed to it into a single
 * string, separated by spaces.  The resulting string is then returned.
 *
 * @param argc The number of arguments passed to the function.
 * @param argv The array of arguments passed to the function.
 *
 * @return The concatenated string.
 */
char *
concat_args(int argc, char **argv)
{
    int i;
    size_t len = 0;
    char *str = NULL;
    char *p;

    /* Calculate the total length of the concatenated string. */
    for (i = 1; i < argc; i++) {
        len += strlen(argv[i]) + 1;
    }

    /* Allocate memory for the concatenated string. */
    str = malloc(len + 1);
    if (str == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Concatenate the arguments into the string. */
    p = str;
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        size_t arg_len = strlen(arg);

        memcpy(p, arg, arg_len);
        p += arg_len;

        *p++ = ' ';
    }

    /* Null-terminate the string. */
    *p = '\0';

    return str;
}

/*
 * This is the main function of the program.  It is responsible for parsing
 * the command line arguments and evaluating the expression.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The array of arguments passed to the program.
 *
 * @return The exit status of the program.
 */
int
main(int argc, char **argv)
{
    char *expr;
    int result;

    /* Check if the correct number of arguments were passed. */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Concatenate the arguments into a single expression. */
    expr = concat_args(argc, argv);

    /* Evaluate the expression. */
    result = system(expr);

    /* Free the memory allocated for the expression. */
    free(expr);

    /* Return the result of the evaluation. */
    return result;
}
#
