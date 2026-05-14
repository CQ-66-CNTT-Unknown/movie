#pragma once

/**
 * @brief Parse a CSV line into individual fields
 * @param line The input string containing the CSV line
 * @param fields An array to store the parsed fields
 * @param max_fields The maximum number of fields to parse
 */
void parse_csv_line(char *line, char *fields[], int max_fields);