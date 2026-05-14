#ifndef SEAT_UTILS_H
#define SEAT_UTILS_H

#include "raylib.h" // For Rectangle, Color, Vector2

#define ROWS 5
#define COLS 5

int isValidSeat(const char *seat);
int isCoupleSeat(const char *seat);

void generateRandomBooked(const char *screeningID);
int isRandomBooked(const char *seat);
int seatBooked(const char *screeningID, const char *seat);
void drawSeatMap(Vector2 mouse);

#endif