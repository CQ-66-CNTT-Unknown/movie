#pragma once

#define LINE_DATA_MAX_SIZE 1024
#define LINE_DATA_BUFFER_SIZE (LINE_DATA_MAX_SIZE + 2) // +2 for newline and null terminator

#define MOVIE_SOURCE_PATH "data/movie.csv"
#define SCREENING_SOURCE_PATH "data/screening.csv"
#define TICKET_SOURCE_PATH "data/ticket.csv"

#define N_MOVIES_FIELDS 3
#define N_SCREENING_FIELDS 5
#define N_TICKETS_FIELDS 4