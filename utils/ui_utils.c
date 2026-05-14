#include "raylib.h"
#include "ui_utils.h"

void drawHeader(const char *title) {
    DrawRectangle(0, 0, 1280, 68, (Color){227,27,35,255});
    /* thin film-strip accents */
    for(int i = 0; i < 16; i++) {
        DrawRectangle(i*22, 0, 14, 68, (Color){200,20,25,255});
        DrawRectangle(i*22+2, 6,  10, 14, (Color){160,10,15,200});
        DrawRectangle(i*22+2, 48, 10, 14, (Color){160,10,15,200});
    }
    /* clean center */
    DrawRectangle(220, 0, 840, 68, (Color){227,27,35,255});
    int tw = MeasureText(title, 32);
    DrawText(title, 640 - tw/2, 18, 32, WHITE);
    /* right logo */
    DrawText("CGV", 1100, 12, 42, (Color){255,220,220,255});
}

int drawBackBtn(Vector2 m) {
    Rectangle btn = {40, 654, 148, 44};
    Color bc = CheckCollisionPointRec(m, btn) ? (Color){80,80,80,255} : (Color){50,50,50,255};
    DrawRectangleRounded(btn, 0.2f, 6, bc);
    DrawText("< QUAY LAI", 55, 666, 20, (Color){220,220,220,255});
    return CheckCollisionPointRec(m, btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}