#include "../../include/utils/input_utils.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *@brief Handle user input for any action that requires ID input (e.g., movie ID)
 *@param user_input The raw input string from the user
 *@return The parsed integer ID if valid, or -1 if the input is invalid
 */
static int handle_input_id(const char *user_input) {
    if (user_input == NULL || *user_input == '\0')
        return -1;

    char *p_end;
    errno = 0;

    long value = strtol(user_input, &p_end, 10);

    if (*p_end != '\0' || errno == ERANGE || value > INT_MAX || value < 0)
        return -1;

    return (int) value;
}


int input_id(const char *prompt, int buffer_size) {
    char user_input[buffer_size];
    printf("%s", prompt);
    fgets(user_input, buffer_size, stdin);

    char *newline = strchr(user_input, '\n');
    if (newline)
        *newline = '\0';
    else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) // Clear buffer to avoid unexpected input next time.
            ;
    }

    return handle_input_id(user_input);
}
