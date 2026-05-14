#include "seat_screen.h"
#include "../project/globals.h"
#include "../utils/seat_utils.h"
#include "../utils/ui_utils.h"
#include <string.h>
#include <stdio.h> // For TextFormat

void DrawSeatScreen(Vector2 m) {
    drawHeader("CHON GHE NGOI");
    drawSeatMap(m); // Pass mouse position to drawSeatMap

    /* Selected seat info bar */
    if(strlen(seatInput) > 0) {
        int bp = isCoupleSeat(seatInput) ? 80000 : 40000;
        const char *tag = isCoupleSeat(seatInput) ? "  [Ghe doi]" : "";
        DrawText(TextFormat("Da chon: %s  |  Gia: %d VND%s", seatInput, bp, tag),
                 390, 628, 22, (Color){255,220,80,255});
    } else {
        DrawText("Nhan vao ghe de chon", 498, 630, 22, (Color){140,140,140,255});
    }

    /* Next button */
    Rectangle nextBtn = {960, 620, 258, 58};
    int canNext = strlen(seatInput) > 0;
    Color nb = canNext
               ? (CheckCollisionPointRec(m, nextBtn)
                  ? (Color){50,200,55,255} : (Color){28,160,35,255})
               : (Color){50,50,50,255};
    DrawRectangleRounded(nextBtn, 0.15f, 6, nb);
    DrawText("TIEP THEO  >", 988, 638, 24, WHITE);

    if(CheckCollisionPointRec(m, nextBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(canNext) { currentScreen = SCREEN_SERVICE; message[0] = '\0'; }
        else          strcpy(message, "Vui long chon ghe!");
    }

    if(drawBackBtn(m)) currentScreen = SCREEN_SHOWTIME;
}