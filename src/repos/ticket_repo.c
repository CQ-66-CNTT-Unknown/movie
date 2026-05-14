#include "../../include/repos/ticket_repo.h"
#include "../../include/constanst.h"
#include "../../include/utils/csv_utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TicketArray *get_all_tickets(const char *ticket_source_path) {
    FILE *ticket_source = fopen(ticket_source_path, "r");
    if (ticket_source == NULL) {
        fprintf(stderr, "Error opening ticket source file: %s\n", ticket_source_path);
        return NULL;
    }

    TicketArray *ticket_array = (TicketArray *) malloc(sizeof(TicketArray));
    if (ticket_array == NULL) {
        fprintf(stderr, "Memory allocation failed for loading tickets\n");
        fclose(ticket_source);
        return NULL;
    }

    ticket_array->tickets = NULL;
    ticket_array->count = 0;
    ticket_array->capacity = 0;

    char buffer[LINE_DATA_BUFFER_SIZE];
    fgets(buffer, sizeof(buffer), ticket_source); // Skip header line

    while (fgets(buffer, sizeof(buffer), ticket_source)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *fields[N_TICKETS_FIELDS];
        parse_csv_line(buffer, fields, N_TICKETS_FIELDS);

        if (ticket_array->count >= ticket_array->capacity) {
            int new_capacity = (ticket_array->capacity == 0) ? 4 : ticket_array->capacity * 2;
            Ticket *new_tickets = (Ticket *) realloc(ticket_array->tickets, new_capacity * sizeof(Ticket));

            if (new_tickets == NULL) {
                fprintf(stderr, "Memory allocation failed for loading tickets\n");
                free(ticket_array->tickets);
                fclose(ticket_source);
                free(ticket_array);
                return NULL;
            }

            ticket_array->tickets = new_tickets;
            ticket_array->capacity = new_capacity;
        }

        Ticket *current_ticket = &ticket_array->tickets[ticket_array->count];

        current_ticket->ticket_id = atoi(fields[0]);
        current_ticket->screening_id = atoi(fields[1]);
        current_ticket->customer_id = atoi(fields[2]);

        strncpy(current_ticket->seat_code, fields[3], sizeof(current_ticket->seat_code) - 1);
        current_ticket->seat_code[sizeof(current_ticket->seat_code) - 1] = '\0';

        ticket_array->count++;
    }

    fclose(ticket_source);
    return ticket_array;
}
