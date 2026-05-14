#pragma once

#include "../models/ticket.h"

#include <stdio.h>

/**
 * @brief Retrieves all tickets from the specified source
 * @param ticket_source_path The file path to the ticket source
 * @return pointer to TicketArray containing all retrieved tickets or `NULL` if an error occurs
 */
TicketArray *get_all_tickets(const char *ticket_source_path);
