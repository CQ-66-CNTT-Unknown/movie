#include "history_screen.h"
#include "../project/globals.h"
#include "../utils/ui_utils.h"
#include "../models/ticket.h"
#include <stdio.h>
#include <string.h>

void DrawHistoryScreen(Vector2 m) {
    drawHeader("LICH SU MUA VE");

    DrawRectangleRounded((Rectangle){20, 82, 1240, 588}, 0.02f, 5,
                          (Color){22,22,22,255});
    DrawRectangleRoundedLines((Rectangle){20, 82, 1240, 588}, 0.02f, 5,
                              (Color){55,55,55,255});

    /* Table header */
    DrawRectangle(21, 83, 1238, 44, (Color){32,32,32,255});
    DrawText("MA VE",       55,  96, 18, (Color){180,180,180,255});
    DrawText("PHIM",       310,  96, 18, (Color){180,180,180,255});
    DrawText("SUAT CHIEU", 590,  96, 18, (Color){180,180,180,255});
    DrawText("GHE",        820,  96, 18, (Color){180,180,180,255});
    DrawText("GIA",       1020,  96, 18, (Color){180,180,180,255});
    DrawRectangle(20, 127, 1240, 1, (Color){48,48,48,255});

    FILE *fp = fopen("data/tickets.csv", "r");
    int y = 132, cnt = 0;
    if(fp) {
        Ticket t;
        while(fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                     t.ticketID, t.userID, t.screeningID, t.movieName,
                     t.showtime, t.seatCode, &t.price, &t.room) == 8) {
            if(strcmp(t.userID, currentUserID) == 0 && y < 650) {
                Color rowBg = (cnt%2==0) ? (Color){26,26,26,255}
                                         : (Color){30,30,30,255};
                DrawRectangle(21, y, 1238, 40, rowBg);
                DrawText(t.ticketID,  55,  y+11, 17, (Color){255,200,80,255});
                DrawText(t.movieName, 310, y+11, 17, WHITE);
                DrawText(t.showtime,  590, y+11, 17, (Color){180,220,255,255});
                DrawText(t.seatCode,  820, y+11, 17, (Color){140,255,140,255});
                DrawText(TextFormat("%d VND", t.price), 1020, y+11, 17,
                         (Color){255,220,50,255});
                y += 43;
                cnt++;
            }
        }
        fclose(fp);
    }
    if(cnt == 0)
        DrawText("Chua co ve nao duoc mua", 480, 370, 24, (Color){90,90,90,255});

    if(drawBackBtn(m)) currentScreen = SCREEN_MENU;
}