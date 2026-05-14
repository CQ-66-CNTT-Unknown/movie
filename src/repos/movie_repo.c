#include "../../include/repos/movie_repo.h"
#include "../../include/constanst.h"
#include "../../include/utils/csv_utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MovieArray *get_all_movies(const char *movie_source_path) {
    MovieArray *movie_array = (MovieArray *) malloc(sizeof(MovieArray));
    if (movie_array == NULL) {
        fprintf(stderr, "Memory allocation failed for MovieArray\n");
        return NULL;
    }

    FILE *movie_source = fopen(movie_source_path, "r");
    if (movie_source == NULL) {
        fprintf(stderr, "Failed to open movie source file: %s\n", movie_source_path);
        free(movie_array);
        return NULL;
    }

    movie_array->movies = NULL;
    movie_array->count = 0;
    movie_array->capacity = 0;

    char buffer[LINE_DATA_BUFFER_SIZE];
    fgets(buffer, sizeof(buffer), movie_source); // Skip header line

    while (fgets(buffer, sizeof(buffer), movie_source)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *fields[N_MOVIES_FIELDS];
        parse_csv_line(buffer, fields, N_MOVIES_FIELDS);

        if (movie_array->count >= movie_array->capacity) {
            int new_capacity = (movie_array->capacity == 0) ? 4 : movie_array->capacity * 2;
            Movie *new_movies = (Movie *) realloc(movie_array->movies, new_capacity * sizeof(Movie));

            if (new_movies == NULL) {
                fprintf(stderr, "Memory allocation failed for loading movies\n");
                free(movie_array->movies);
                free(movie_array);
                fclose(movie_source);
                return NULL;
            }

            movie_array->movies = new_movies;
            movie_array->capacity = new_capacity;
        }

        Movie *current_movie = &movie_array->movies[movie_array->count];

        current_movie->movie_id = atoi(fields[0]);

        strncpy(current_movie->title, fields[1], sizeof(current_movie->title) - 1);
        current_movie->title[sizeof(current_movie->title) - 1] = '\0';

        current_movie->duration = atoi(fields[2]);

        movie_array->count++;
    }

    return movie_array;
}


Movie *delete_movie_record(int movie_id, const char *movie_source_path) {
    FILE *movie_source = fopen(movie_source_path, "r");
    if (movie_source == NULL) {
        fprintf(stderr, "Failed to open movie source file: %s\n", movie_source_path);
        return NULL;
    }

    char *last_slash = strrchr(movie_source_path, '/');
#ifdef _WIN32
    if (last_slash == NULL)
        last_slash = strrchr(movie_source_path, '\\');
#endif

    char temp_file_path[256];
    if (last_slash != NULL) {
        size_t dir_length = last_slash - movie_source_path + 1;
        strncpy(temp_file_path, movie_source_path, dir_length);
        temp_file_path[dir_length] = '\0';
        strcat(temp_file_path, "temp_movie.csv");
    } else {
        strncpy(temp_file_path, "temp_movie.csv", sizeof(temp_file_path) - 1);
        temp_file_path[sizeof(temp_file_path) - 1] = '\0';
    }

    FILE *temp_file = fopen(temp_file_path, "w");
    if (temp_file == NULL) {
        fprintf(stderr, "Failed to create temporary file for movie deletion\n");
        fclose(movie_source);
        return NULL;
    }

    Movie *deleted_movie = NULL;

    char buffer[LINE_DATA_BUFFER_SIZE];
    fgets(buffer, LINE_DATA_BUFFER_SIZE, movie_source); // Read and write header line
    fprintf(temp_file, "%s", buffer);

    while (fgets(buffer, LINE_DATA_BUFFER_SIZE, movie_source)) {
        char temp_buffer[LINE_DATA_BUFFER_SIZE];
        strcpy(temp_buffer, buffer);

        char *fields[N_MOVIES_FIELDS];
        parse_csv_line(buffer, fields, N_MOVIES_FIELDS);

        if (atoi(fields[0]) != movie_id) {
            fprintf(temp_file, "%s", temp_buffer);
        } else {
            deleted_movie = (Movie *) malloc(sizeof(Movie));
            if (deleted_movie == NULL) {
                fprintf(stderr, "Memory allocation failed for deleted movie record\n");
                fclose(movie_source);
                fclose(temp_file);
                return NULL;
            }
            deleted_movie->movie_id = atoi(fields[0]);
            strncpy(deleted_movie->title, fields[1], sizeof(deleted_movie->title) - 1);
            deleted_movie->title[sizeof(deleted_movie->title) - 1] = '\0';
            deleted_movie->duration = atoi(fields[2]);
        }
    }

    fclose(movie_source);
    fclose(temp_file);

    if (remove(movie_source_path) != 0) {
        fprintf(stderr, "Failed to delete original movie source file: %s\n", movie_source_path);
        return NULL;
    }

    if (rename(temp_file_path, movie_source_path) != 0) {
        fprintf(stderr, "Failed to rename temporary file to original movie source file: %s\n", movie_source_path);
        return NULL;
    }

    return deleted_movie;
}
