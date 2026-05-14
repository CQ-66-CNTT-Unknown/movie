#include "screens/showtime_screen.h"
#include "../project/globals.h"
#include "../utils/ui_utils.h"
#include "../utils/input_utils.h"
#include "../utils/seat_utils.h"
#include "../models/showtime.h"
#include <string.h>
#include <stdio.h> // For TextFormat

void DrawShowtimeScreen(Vector2 m) {
    drawHeader("CHON SUAT CHIEU");

    /* Left panel: 3 movie groups in columns */
    DrawRectangleRounded((Rectangle){20, 82, 790, 610}, 0.02f, 5,
                          (Color){22,22,22,255});
    DrawRectangleRoundedLines((Rectangle){20, 82, 790, 610}, 0.02f, 5,
                              (Color){55,55,55,255});

    const char *movies[]    = {"Quy Cau",  "Phi Phong", "Mua Do"};
    int         startIdx[]  = {0, 4, 8};
    Color       mColors[]   = {{80,30,120,255},{20,80,145,255},{20,115,60,255}};

    for(int mi = 0; mi < 3; mi++) {
        int bx = 40 + mi * 262;
        int by = 96;

        /* Movie header pill */
        DrawRectangleRounded((Rectangle){bx, by, 242, 42}, 0.2f, 6, mColors[mi]);
        DrawText(movies[mi], bx+10, by+11, 22, WHITE);

        for(int si = 0; si < 4; si++) {
            int idx = startIdx[mi] + si;
            int sy  = by + 52 + si * 136;

            DrawRectangleRounded((Rectangle){bx, sy, 242, 122}, 0.08f, 5,
                                  (Color){32,32,32,255});
            DrawRectangleRoundedLines((Rectangle){bx, sy, 242, 122}, 0.08f, 5,
                                      (Color){65,65,65,255});
            DrawText(TextFormat("ID: %s", showtimes[idx].id),
                     bx+10, sy+10, 17, (Color){190,190,190,255});
            DrawText(showtimes[idx].time, bx+10, sy+36, 36, WHITE);
            DrawText("Phong 1  |  40.000 VND",
                     bx+10, sy+82, 15, (Color){130,130,130,255});
            DrawText("Ghe doi: 80.000 VND",
                     bx+10, sy+102, 14, (Color){200,158,0,255});
        }
    }

    /* ---- Right input panel (moved up) ---- */
    DrawRectangleRounded((Rectangle){830, 82, 430, 210}, 0.05f, 8,
                          (Color){22,22,22,255});
    DrawRectangleRoundedLines((Rectangle){830, 82, 430, 210}, 0.05f, 8,
                              (Color){227,27,35,200});

    DrawText("NHAP ID SUAT CHIEU:", 855, 104, 20, (Color){210,210,210,255});

    /* Input box */
    Rectangle inputBox = {855, 140, 375, 56};
    Color ibg = (typingField == 1) ? (Color){248,248,255,255}
                                   : (Color){232,232,242,255};
    DrawRectangleRounded(inputBox, 0.1f, 6, ibg);
    if(typingField == 1)
        DrawRectangleRoundedLines(inputBox, 0.1f, 6, (Color){227,27,35,255});
    DrawText(screeningInput, 870, 156, 28, (Color){20,20,20,255});
    /* Blinking cursor */
    if(typingField == 1 && ((int)(GetTime()*2) % 2 == 0))
        DrawRectangle(870 + MeasureText(screeningInput, 28), 157, 2, 28,
                      (Color){20,20,20,255});

    if(CheckCollisionPointRec(m, inputBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        typingField = 1;
    if(typingField == 1) HandleTextInput(screeningInput, 30);

    /* Next button */
    Rectangle nextBtn = {855, 220, 375, 58};
    Color nb = CheckCollisionPointRec(m, nextBtn)
               ? (Color){50,200,55,255} : (Color){28,160,35,255};
    DrawRectangleRounded(nextBtn, 0.15f, 6, nb);
    DrawText("TIEP THEO  >", 960, 238, 26, WHITE);

    if(CheckCollisionPointRec(m, nextBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(strlen(screeningInput) > 0) {
            generateRandomBooked(screeningInput);
            currentScreen = SCREEN_SEAT;
            message[0] = '\0';
        } else {
            strcpy(message, "Vui long nhap ID suat chieu!");
        }
    }

    if(drawBackBtn(m)) { currentScreen = SCREEN_MENU; typingField = 0; }
}