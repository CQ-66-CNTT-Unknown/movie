#include "../../include/utils/csv_utils.h"

#include <stdbool.h>

/**
 * @brief Remove surrounding quotes from a CSV field
 * @param field The field to trim
 */
static void trim_quotes(char *field) {
    if (field[0] == '"') {
        field++;
    }

    char *end = field;
    while (*end != '\0') {
        end++;
    }

    if (end > field && *(end - 1) == '"') {
        *(end - 1) = '\0';
    }
}

void parse_csv_line(char *line, char *fields[], int max_fields) {
    int field_count = 0;
    bool in_quotes = false;

    fields[field_count] = &line[0];
    trim_quotes(fields[0]);
    field_count++;

    for (int i = 0; line[i] != '\0' && field_count < max_fields; i++) {
        if (line[i] == '"') {
            in_quotes = !in_quotes;
        } else if (line[i] == ',' && !in_quotes) {
            line[i] = '\0';
            fields[field_count] = &line[i + 1];
            trim_quotes(fields[field_count]);
            field_count++;
        }
    }
}
