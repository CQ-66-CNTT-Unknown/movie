#include "menu_screen.h"
#include "../project/globals.h"
#include "../utils/ui_utils.h"
#include "raylib.h"

void DrawMenuScreen(Vector2 m) {
    /* ---- Header ---- */
    DrawRectangle(0, 0, 1280, 115, (Color){227,27,35,255});
    /* Film-strip edges */
    for(int i = 0; i < 16; i++) {
        DrawRectangle(i*22, 0, 14, 115, (Color){200,20,25,255});
        DrawRectangle(i*22+2, 8,  10, 16, (Color){150,10,12,200});
        DrawRectangle(i*22+2, 91, 10, 16, (Color){150,10,12,200});
    }
    for(int i = 0; i < 16; i++) {
        DrawRectangle(1280-i*22-16, 0, 14, 115, (Color){200,20,25,255});
        DrawRectangle(1280-i*22-14, 8,  10, 16, (Color){150,10,12,200});
        DrawRectangle(1280-i*22-14, 91, 10, 16, (Color){150,10,12,200});
    }
    DrawRectangle(280, 0, 720, 115, (Color){227,27,35,255}); /* clean middle */
    DrawText("CGV",     490, 10, 82, WHITE);
    DrawText("CINEMAS", 680, 30, 46, (Color){255,210,210,255});

    /* ---- Tagline ---- */
    DrawText("Trai nghiem phim anh dang cap",
             450, 143, 22, (Color){160,160,160,255});
    DrawRectangle(440, 171, 400, 1, (Color){227,27,35,150});

    /* ---- Menu buttons ---- */
    Rectangle b1 = {490, 195, 300, 72};
    Rectangle b2 = {490, 310, 300, 72};
    Rectangle b3 = {490, 425, 300, 72};

    /* DAT VE (red, primary) */
    Color b1c = CheckCollisionPointRec(m, b1)
                ? (Color){255,55,60,255} : (Color){227,27,35,255};
    DrawRectangleRounded(b1, 0.14f, 10, b1c);
    DrawText("DAT VE", 591, 218, 30, WHITE);

    /* HUY VE */
    Color b2c = CheckCollisionPointRec(m, b2)
                ? (Color){58,58,58,255} : (Color){35,35,35,255};
    DrawRectangleRounded(b2, 0.14f, 10, b2c);
    DrawRectangleRoundedLines(b2, 0.14f, 10, (Color){90,90,90,255});
    DrawText("HUY VE", 591, 333, 30, WHITE);

    /* LICH SU */
    Color b3c = CheckCollisionPointRec(m, b3)
                ? (Color){58,58,58,255} : (Color){35,35,35,255};
    DrawRectangleRounded(b3, 0.14f, 10, b3c);
    DrawRectangleRoundedLines(b3, 0.14f, 10, (Color){90,90,90,255});
    DrawText("LICH SU", 587, 448, 30, WHITE);

    /* ---- Footer ---- */
    DrawRectangle(0, 686, 1280, 34, (Color){22,22,22,255});
    DrawRectangle(0, 685, 1280, 1,  (Color){55,55,55,255});
    DrawText("© CGV Cinemas Vietnam  |  Hotline: 1900 6017",
             415, 697, 16, (Color){110,110,110,255});

    if(CheckCollisionPointRec(m, b1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        { currentScreen = SCREEN_SHOWTIME; message[0] = '\0'; }
    if(CheckCollisionPointRec(m, b2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        { currentScreen = SCREEN_CANCEL; message[0] = '\0'; typingField = 0; }
    if(CheckCollisionPointRec(m, b3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        { currentScreen = SCREEN_HISTORY; message[0] = '\0'; }
}