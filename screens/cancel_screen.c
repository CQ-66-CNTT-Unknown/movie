#include "cancel_screen.h"
#include "../project/globals.h"
#include "../utils/input_utils.h"
#include "../utils/ui_utils.h"
#include "../models/ticket.h"
#include <stdio.h>
#include <string.h>

void DrawCancelScreen(Vector2 m) {
    drawHeader("HUY VE");

    /* ---- Left: ticket history ---- */
    DrawRectangleRounded((Rectangle){15, 82, 760, 610}, 0.02f, 5,
                          (Color){22,22,22,255});
    DrawRectangleRoundedLines((Rectangle){15, 82, 760, 610}, 0.02f, 5,
                              (Color){55,55,55,255});

    DrawText("VE DA MUA CUA BAN:", 35, 96, 20, (Color){190,190,190,255});
    DrawRectangle(15, 124, 760, 1, (Color){48,48,48,255});

    /* Header row */
    DrawRectangle(16, 125, 759, 32, (Color){30,30,30,255});
    DrawText("MA VE",       40,  133, 17, (Color){170,170,170,255});
    DrawText("PHIM",       260,  133, 17, (Color){170,170,170,255});
    DrawText("SUAT",       490,  133, 17, (Color){170,170,170,255});
    DrawText("GHE",        600,  133, 17, (Color){170,170,170,255});
    DrawText("GIA",        680,  133, 17, (Color){170,170,170,255});

    FILE *histFp = fopen("data/tickets.csv", "r");
    int hy = 160, cnt = 0;
    if(histFp) {
        Ticket t;
        while(fscanf(histFp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                     t.ticketID, t.userID, t.screeningID, t.movieName,
                     t.showtime, t.seatCode, &t.price, &t.room) == 8) {
            if(strcmp(t.userID, currentUserID) == 0 && hy < 670) {
                Color rowBg = (cnt%2==0) ? (Color){26,26,26,255}
                                         : (Color){30,30,30,255};
                DrawRectangle(16, hy, 759, 42, rowBg);
                DrawText(t.ticketID,  40,  hy+13, 16, (Color){255,200,80,255});
                DrawText(t.movieName, 260, hy+13, 16, WHITE);
                DrawText(t.showtime,  490, hy+13, 16, (Color){180,220,255,255});
                DrawText(t.seatCode,  600, hy+13, 16, (Color){140,255,140,255});
                DrawText(TextFormat("%dK", t.price/1000), 680, hy+13, 16,
                         (Color){255,220,50,255});
                hy += 44;
                cnt++;
            }
        }
        fclose(histFp);
    }
    if(cnt == 0)
        DrawText("Chua co ve nao", 300, 380, 22, (Color){90,90,90,255});

    /* ---- Right: cancel form ---- */
    DrawRectangleRounded((Rectangle){792, 82, 472, 270}, 0.04f, 6,
                          (Color){22,22,22,255});
    DrawRectangleRoundedLines((Rectangle){792, 82, 472, 270}, 0.04f, 6,
                              (Color){227,27,35,180});

    DrawText("NHAP MA VE CAN HUY:", 820, 104, 20, WHITE);

    Rectangle inputBox = {820, 142, 416, 58};
    Color ibg = (typingField == 3) ? (Color){248,248,255,255}
                                   : (Color){232,232,242,255};
    DrawRectangleRounded(inputBox, 0.1f, 5, ibg);
    if(typingField == 3)
        DrawRectangleRoundedLines(inputBox, 0.1f, 5, (Color){227,27,35,255});
    DrawText(cancelInput, 835, 158, 24, (Color){20,20,20,255});
    if(typingField == 3 && ((int)(GetTime()*2) % 2 == 0))
        DrawRectangle(835 + MeasureText(cancelInput, 24), 159, 2, 24,
                      (Color){20,20,20,255});

    if(CheckCollisionPointRec(m, inputBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        typingField = 3;
    if(typingField == 3) HandleTextInput(cancelInput, 30);

    DrawText("(Copy ma ve tu bang ben trai)", 820, 212, 17, (Color){110,110,110,255});

    Rectangle cancelBtn = {830, 242, 400, 62};
    Color cbc = CheckCollisionPointRec(m, cancelBtn)
                ? (Color){220,40,40,255} : (Color){175,18,18,255};
    DrawRectangleRounded(cancelBtn, 0.15f, 6, cbc);
    DrawText("XAC NHAN HUY VE", 882, 261, 26, WHITE);

    if(CheckCollisionPointRec(m, cancelBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        cancelTicket();

    if(drawBackBtn(m)) { currentScreen = SCREEN_MENU; typingField = 0; }
}