#pragma once

/**
 * @brief Ticket structure representing a ticket in the system
 */
typedef struct Ticket {
    int ticket_id; /**< The unique identifier for the ticket */
    int screening_id; /**< The ID of the screening for which the ticket is booked */
    int customer_id; /**< The ID of the customer who booked the ticket */
    char seat_code[3]; /**< The code representing the seat location (included null terminator, e.g., "A1") */
} Ticket;


/**
 * @brief Dynamic array structure to hold multiple tickets
 */
typedef struct TicketArray {
    Ticket *tickets; /**< Pointer to an array of Ticket structures */
    int count; /**< The number of tickets in the array */
    int capacity; /**< The maximum number of tickets the array can hold */
} TicketArray;