#pragma once

#include <time.h>

/**
 * @brief Screening structure representing a movie screening in the system
 */
typedef struct Screening {
    int screening_id; /**< The unique identifier for the screening */
    int movie_id; /**< The ID of the movie being screened */
    time_t start_time; /**< The start time of the screening */
    double price; /**< The price of a ticket for the screening */
    int room_number; /**< The room number where the screening is taking place */
} Screening;

/**
 * @brief Dynamic array structure to hold multiple screenings
 */
typedef struct ScreeningArray {
    Screening *screenings; /**< Pointer to an array of Screening structures */
    int count; /**< The number of screenings currently in the array */
    int capacity; /**< The maximum number of screenings the array can hold */
} ScreeningArray;