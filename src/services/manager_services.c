#include "../../include/services/manager_services.h"
#include "../../include/constanst.h"
#include "../../include/repos/movie_repo.h"
#include "../../include/repos/screening_repo.h"
#include "../../include/repos/ticket_repo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief MovieStats structure representing the statistics of a movie
 */
typedef struct MovieStats {
    char title[100]; /**< The title of the movie */
    int tickets_sold; /**< The number of tickets sold for the movie */
    double revenue; /**< The total revenue generated from ticket sales for the movie */
} MovieStats;

/**
 * @brief Swap two MovieStats structures
 * @param a Pointer to the first MovieStats structure
 * @param b Pointer to the second MovieStats structure
 */
static void swap_movie_stats(MovieStats *a, MovieStats *b) {
    MovieStats temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sort an array of MovieStats by revenue in descending order
 * @param stats The array of MovieStats to sort
 * @param count The number of MovieStats in the array
 */
void sort_movie_stats_by_revenue(MovieStats *stats, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (stats[j].revenue < stats[j + 1].revenue) {
                swap_movie_stats(&stats[j], &stats[j + 1]);
            }
        }
    }
}

/**
 * @brief Print the header of the revenue report table
 */
static void print_revenue_report_header() {
    printf("%-32s | %-16s | %-16s\n", "Movie Title", "Tickets Sold", "Revenue (VND)");
    int divider_length = 32 + 16 + 16 + (2 * 3); // Total width of the table
    for (int i = 0; i < divider_length; i++)
        printf("-");
    printf("\n");
}

/**
 * @brief Print the statistics of a movie
 * @param stats Pointer to the MovieStats structure containing the movie's statistics
 */
static void print_a_movie_stats(MovieStats *stats) {
    printf("%-32s | %-16d | %-16.0f\n", stats->title, stats->tickets_sold, stats->revenue);
}

/**
 * @brief Print the statistics of multiple movies
 * @param stats Pointer to the array of MovieStats structures
 * @param count The number of MovieStats in the array
 */
static void print_movies_stats(MovieStats *stats, int count) {
    for (int i = 0; i < count; i++) {
        print_a_movie_stats(&stats[i]);
    }
}

/**
 * @brief Get the revenue data for each movie
 * @param stats Pointer to the array of MovieStats structures
 * @param movies_array Pointer to the array of movies
 * @param screenings_array Pointer to the array of screenings
 * @param tickets_array Pointer to the array of tickets
 */
static void get_revenue_data(MovieStats *stats, MovieArray *movies_array, ScreeningArray *screenings_array,
                             TicketArray *tickets_array) {
    for (int i = 0; i < movies_array->count; i++) {
        strcpy(stats[i].title, movies_array->movies[i].title);
        stats[i].tickets_sold = 0;
        stats[i].revenue = 0.0;

        for (int j = 0; j < screenings_array->count; j++) {
            if (screenings_array->screenings[j].movie_id == movies_array->movies[i].movie_id) {
                for (int k = 0; k < tickets_array->count; k++) {
                    if (tickets_array->tickets[k].screening_id == screenings_array->screenings[j].screening_id) {
                        stats[i].tickets_sold++;
                        stats[i].revenue += screenings_array->screenings[j].price;
                    }
                }
            }
        }
    }
}

void show_revenue_report() {
    MovieArray *movies_array = get_all_movies(MOVIE_SOURCE_PATH);
    ScreeningArray *screenings_array = get_all_screenings(SCREENING_SOURCE_PATH);
    TicketArray *tickets_array = get_all_tickets(TICKET_SOURCE_PATH);

    if (tickets_array == NULL) {
        fprintf(stderr, "Failed to load ticket data.\n");
        return;
    }

    if (screenings_array == NULL) {
        fprintf(stderr, "Failed to load screening data.\n");
        free(tickets_array);
        return;
    }

    if (movies_array == NULL) {
        fprintf(stderr, "Failed to load movie data.\n");
        free(tickets_array);
        free(screenings_array);
        return;
    }

    MovieStats *stats = (MovieStats *) malloc(movies_array->count * sizeof(MovieStats));
    if (stats == NULL) {
        fprintf(stderr, "Failed to allocate memory for movie statistics.\n");
        return;
    }

    get_revenue_data(stats, movies_array, screenings_array, tickets_array);
    sort_movie_stats_by_revenue(stats, movies_array->count);

    double total_revenue = 0.0;
    int total_tickets_sold = 0;
    // Calculate total revenue and total tickets sold
    for (int i = 0; i < movies_array->count; i++) {
        total_revenue += stats[i].revenue;
        total_tickets_sold += stats[i].tickets_sold;
    }

    printf("Revenue Report:\n");
    print_revenue_report_header();
    print_movies_stats(stats, movies_array->count);
    printf("\n");

    int divider_length = 32 + 16 + 16 + (2 * 3); // Total width of the table
    for (int i = 0; i < divider_length; i++)
        printf("-");
    printf("\n");

    printf("%-32s | %-16d | %-16.0f\n", "Total", total_tickets_sold, total_revenue);

    free(stats);
    free(tickets_array);
    free(screenings_array);
    free(movies_array);
}
