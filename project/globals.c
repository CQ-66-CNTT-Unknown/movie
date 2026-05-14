#include "globals.h"

char currentUserID[] = "USER001";
char message[256] = "";
char screeningInput[30] = "";
char seatInput[10] = "";
char cancelInput[30] = "";
char randomBooked[10][10];
int randomBookedCount = 0;
char lastScreeningForRandom[30] = "";
int typingField = 0;
int buyWater = 0;
int buyPopcorn = 0;

AppScreen currentScreen = SCREEN_MENU;