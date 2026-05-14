#include "service_screen.h"
#include "../project/globals.h"
#include "../utils/ui_utils.h"
#include "../utils/seat_utils.h"
#include "../models/ticket.h"
#include <string.h>
#include <stdio.h> // For TextFormat

void DrawServiceScreen(Vector2 m) {
    drawHeader("DICH VU KEM THEO");

    DrawRectangleRounded((Rectangle){280, 90, 720, 510}, 0.03f, 8,
                          (Color){22,22,22,255});
    DrawText("Them dich vu de co trai nghiem tot hon!",
             340, 115, 22, (Color){160,160,160,255});
    DrawRectangle(280, 148, 720, 1, (Color){48,48,48,255});

    /* Water */
    Rectangle waterBtn = {320, 165, 640, 95};
    Color wc = buyWater ? (Color){18,115,18,255} : (Color){32,32,32,255};
    DrawRectangleRounded(waterBtn, 0.1f, 6, wc);
    DrawRectangleRoundedLines(waterBtn, 0.1f, 6,
                              buyWater ? (Color){50,200,50,120} : (Color){65,65,65,255});
    DrawText("NUOC UONG",          380, 188, 28, WHITE);
    DrawText("+20,000 VND",        380, 224, 21, (Color){190,190,190,255});
    DrawText(buyWater ? "[v] DA CHON" : "[ ] CLICK DE THEM",
             740, 200, 19,
             buyWater ? (Color){140,255,140,255} : (Color){110,110,110,255});

    /* Popcorn */
    Rectangle popBtn = {320, 280, 640, 95};
    Color pc = buyPopcorn ? (Color){18,115,18,255} : (Color){32,32,32,255};
    DrawRectangleRounded(popBtn, 0.1f, 6, pc);
    DrawRectangleRoundedLines(popBtn, 0.1f, 6,
                              buyPopcorn ? (Color){50,200,50,120} : (Color){65,65,65,255});
    DrawText("BAP RANG BOT",       380, 303, 28, WHITE);
    DrawText("+20,000 VND",        380, 339, 21, (Color){190,190,190,255});
    DrawText(buyPopcorn ? "[v] DA CHON" : "[ ] CLICK DE THEM",
             740, 315, 19,
             buyPopcorn ? (Color){140,255,140,255} : (Color){110,110,110,255});

    /* Total */
    DrawRectangle(280, 388, 720, 1, (Color){48,48,48,255});
    int bp    = isCoupleSeat(seatInput) ? 80000 : 40000;
    int total = bp + (buyWater?20000:0) + (buyPopcorn?20000:0);
    DrawText(TextFormat("Tong tien: %d VND", total),
             430, 402, 28, (Color){255,220,50,255});

    /* Book button */
    Rectangle bookBtn = {380, 455, 520, 68};
    Color bbc = CheckCollisionPointRec(m, bookBtn)
                ? (Color){255,55,60,255} : (Color){227,27,35,255};
    DrawRectangleRounded(bookBtn, 0.15f, 8, bbc);
    DrawText("XAC NHAN DAT VE", 462, 475, 28, WHITE);

    if(CheckCollisionPointRec(m, waterBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        buyWater = !buyWater;
    if(CheckCollisionPointRec(m, popBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        buyPopcorn = !buyPopcorn;
    if(CheckCollisionPointRec(m, bookBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        buyTicket();
        currentScreen = SCREEN_HISTORY;
    }

    if(drawBackBtn(m)) currentScreen = SCREEN_SEAT;
}