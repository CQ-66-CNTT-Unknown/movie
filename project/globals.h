#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h" // For Color, Vector2, etc.

typedef enum {
    SCREEN_MENU,
    SCREEN_SHOWTIME,
    SCREEN_SEAT,
    SCREEN_SERVICE,
    SCREEN_CANCEL,
    SCREEN_HISTORY
} AppScreen;

extern char currentUserID[];
extern char message[];
extern char screeningInput[];
extern char seatInput[];
extern char cancelInput[];

extern int typingField;
extern int buyWater;
extern int buyPopcorn;

extern AppScreen currentScreen;

// Random pre-booked seats per screening (session-only, for visual)
extern char randomBooked[10][10];
extern int randomBookedCount;
extern char lastScreeningForRandom[30];

#endif