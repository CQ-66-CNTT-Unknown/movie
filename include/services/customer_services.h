#pragma once

/**
 * @brief Book a ticket for a specific screening
 * @param screening_id The ID of the screening for which to book a ticket
 * @param seat_code The code of the seat to book
 */
void book_ticket(int screening_id, char seat_code);

/**
 * @brief Cancel a booked ticket
 * @param ticket_id The ID of the ticket to cancel
 */
void cancel_ticket(int ticket_id);

/**
 * @brief View purchase history
 */
void view_purchase_history();
