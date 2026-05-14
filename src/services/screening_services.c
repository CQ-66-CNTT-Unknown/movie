#include "../../include/services/screening_services.h"
#include "../../include/constanst.h"
#include "../../include/models/movie.h"
#include "../../include/models/screening.h"
#include "../../include/repos/movie_repo.h"
#include "../../include/repos/screening_repo.h"
#include "../../include/utils/csv_utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Print the header of the screening table
 */
static void print_screening_table_header() {
    printf("%-12s | %-28s | %-28s | %-16s | %-12s | %-8s\n", "Screening ID", "Movie", "Start time", "Duration (m)",
           "Price (VND)", "Room");
    int table_width = 12 + 28 + 28 + 16 + 12 + 8 + (5 * 3);
    for (int i = 0; i < table_width; i++)
        printf("-");
    printf("\n");
}

/**
 * @brief Find a movie by its ID
 * @param movie_array The array of movies
 * @param movie_id The ID of the movie to find
 * @return A pointer to the found movie, or `NULL` if not found
 */
static Movie *find_movie_by_id(const MovieArray *movie_array, int movie_id) {
    for (int i = 0; i < movie_array->count; i++) {
        if (movie_array->movies[i].movie_id == movie_id)
            return &movie_array->movies[i];
    }
    return NULL;
}

/**
 * @brief Print information about a screening
 * @param screening The screening to print information for
 * @param movie The movie associated with the screening
 */
static void print_screening_info(Screening *screening, Movie *movie) {
    char time_str[26];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&screening->start_time));

    printf("%-12d | %-28s | %-28s | %-16d | %-12.0f | %-8d\n", screening->screening_id, movie->title, time_str,
           movie->duration, screening->price, screening->room_number);
}

void view_screenings() {
    MovieArray *movie_array = get_all_movies(MOVIE_SOURCE_PATH);
    ScreeningArray *screening_array = get_all_screenings(SCREENING_SOURCE_PATH);

    if (screening_array == NULL) {
        fprintf(stderr, "Failed to load screening data.\n");
        return;
    }

    if (movie_array == NULL) {
        fprintf(stderr, "Failed to load movie data.\n");
        free(screening_array);
        return;
    }

    if (screening_array->count == 0) {
        fprintf(stderr, "No screenings available.\n");
        free(screening_array);
        free(movie_array);
        return;
    }

    print_screening_table_header();

    for (int i = 0; i < screening_array->count; i++) {
        Screening *current_screening = &screening_array->screenings[i];
        Movie *associated_movie = find_movie_by_id(movie_array, current_screening->movie_id);

        if (associated_movie != NULL) {
            print_screening_info(current_screening, associated_movie);
        } else {
            fprintf(stderr, "Warning: Movie with ID %d not found for screening ID %d\n", current_screening->movie_id,
                    current_screening->screening_id);
        }
    }

    free(screening_array);
    free(movie_array);
}

void show_seat_map(int screening_id) {
    // TODO
}

void create_screening(int movie_id) {
    // TODO
}

void cancel_screening() {
    // TODO
}
