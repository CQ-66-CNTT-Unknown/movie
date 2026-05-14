#pragma once

/**
 * @brief View all screenings
 */
void view_screenings();

/**
 * @brief Show the seat map for a specific screening
 * @param screening_id The ID of the screening for which to show the seat map
 */
void show_seat_map(int screening_id);

/**
 * @brief Create a new screening
 * @param movie_id The ID of the movie for which the screening is to be created
 */
void create_screening(int movie_id);

/**
 * @brief Cancel an existing screening
 */
void cancel_screening();
