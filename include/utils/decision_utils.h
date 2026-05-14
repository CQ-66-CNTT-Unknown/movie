#pragma once

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Prompts the user with a yes/no question and returns their decision
 * @param prompt The question to present to the user
 * @return `true` if the user responds with 'y' or 'Y', `false` otherwise
 */
bool is_decision_yes(const char *prompt);
