#pragma once

/**
 *@brief Movie structure representing a movie in the system
 */
typedef struct Movie {
    int movie_id; /**< The unique identifier for the movie */
    char title[100]; /**< The title of the movie */
    int duration; /**< The duration of the movie in minutes */
} Movie;

/**
 *@brief Dynamic array structure to hold multiple movies
 */
typedef struct MovieArray {
    Movie *movies; /**< Pointer to an array of Movie structures */
    int count; /**< The number of movies currently in the array */
    int capacity; /**< The maximum number of movies the array can hold */
} MovieArray;
