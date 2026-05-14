#pragma once

/**
 * @brief Display all available movies
 *
 */
void display_all_movies();

/**
 * @brief Search for a movie by name
 * @param name The name of the movie to search for
 */
void search_movie_by_name(const char *name);

/**
 * @brief Add a new movie to data
 */
void add_movie();

/**
 * @brief Edit an existing movie in data
 * @param movie_id The ID of the movie to be edited
 */
void edit_movie(int movie_id);

/**
 * @brief Delete a movie from data
 * @param movie_id The ID of the movie to be deleted
 */
void delete_movie(int movie_id);
