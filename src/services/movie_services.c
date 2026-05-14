#include "../../include/services/movie_services.h"
#include "../../include/constanst.h"
#include "../../include/repos/movie_repo.h"
#include "../../include/repos/screening_repo.h"
#include "../../include/utils/decision_utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_all_movies() {
    // TODO
}

void search_movie_by_name(const char *name) {
    // TODO
}

void add_movie() {
    // TODO
}

void edit_movie(int movie_id) {
    // TODO
}

/**
 * @brief Prints the details of a movie to the console
 * @param movie Pointer to the Movie struct whose details are to be printed
 */
static void print_movie_details(const Movie *movie) {
    printf("Movie Details:\n");
    printf("ID: %d\n", movie->movie_id);
    printf("Title: %s\n", movie->title);
    printf("Duration: %d minutes\n", movie->duration);
}

void delete_movie(int movie_id) {
    if (movie_id == -1) {
        printf("The ID is invalid!\n");
        return;
    }

    bool is_scheduled = is_movie_scheduled(movie_id, SCREENING_SOURCE_PATH);

    if (is_scheduled) {
        printf("The movie is scheduled, please cancel all related screenings before deleting the movie!\n");
        return;
    }

    if (!is_decision_yes("Delete movie with ID"))
        return;

    Movie *deleted_movie = delete_movie_record(movie_id, MOVIE_SOURCE_PATH);
    if (deleted_movie != NULL) {
        printf("Movie deleted successfully!\n");
        print_movie_details(deleted_movie);
        free(deleted_movie);
    } else {
        printf("Failed to delete the movie.\n");
    }
}