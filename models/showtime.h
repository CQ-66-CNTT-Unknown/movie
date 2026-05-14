#ifndef SHOWTIME_H
#define SHOWTIME_H

typedef struct {
    char id[10];
    char movie[100];
    char time[20];
} Showtime;

extern Showtime showtimes[];
extern int showtimeCount;

#endif