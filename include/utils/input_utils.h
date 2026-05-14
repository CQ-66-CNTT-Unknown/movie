#pragma once

/**
 *@brief Prompt the user for an ID input and validate it
 *@param prompt The message to display to the user when asking for input
 *@param buffer_size The size of the input buffer to read the user's input
 *@return The valid integer ID entered by the user, or -1 if the input is invalid
 */
int input_id(const char *prompt, int buffer_size);