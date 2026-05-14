#include "raylib.h"
#include <stdlib.h> 
#include <time.h> 
#include <string.h> 
#include "project/globals.h"
#include "models/showtime.h"
#include "models/ticket.h"
#include "screens/menu_screen.h"
#include "screens/showtime_screen.h"
#include "screens/seat_screen.h"
#include "screens/service_screen.h"
#include "screens/cancel_screen.h"
#include "screens/history_screen.h"
int main() {
    srand(time(NULL)); // Initialize random seed

    InitWindow(1280, 720, "CGV Cinemas - Dat Ve");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        Vector2 m = GetMousePosition(); // Mouse position is needed in multiple screens

        BeginDrawing();
        ClearBackground((Color){15,15,15,255}); // Moved from individual screens to here

        switch(currentScreen) {
            case SCREEN_MENU:
                DrawMenuScreen(m);
                break;
            case SCREEN_SHOWTIME:
                DrawShowtimeScreen(m);
                break;
            case SCREEN_SEAT:
                DrawSeatScreen(m);
                break;
            case SCREEN_SERVICE:
                DrawServiceScreen(m);
                break;
            case SCREEN_CANCEL:
                DrawCancelScreen(m);
                break;
            case SCREEN_HISTORY:
                DrawHistoryScreen(m);
                break;
        }

        /* ---- Global message toast ---- */
        if(strlen(message) > 0) {
            int mw = MeasureText(message, 21);
            DrawRectangleRounded((Rectangle){(float)(640 - mw/2 - 16), 688,
                                             (float)(mw + 32), 28},
                                  0.3f, 5, (Color){35,35,0,220});
            DrawText(message, 640 - mw/2, 695, 21, (Color){255,230,50,255});
        }

        if(IsKeyPressed(KEY_ESCAPE)) {
            currentScreen = SCREEN_MENU;
            typingField = 0;
            message[0] = '\0';
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}