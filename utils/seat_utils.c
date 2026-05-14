#include "utils/seat_utils.h"
#include "../models/ticket.h"
#include "../project/globals.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // For rand()

/* Row E = couple seat (gia gap doi) */
int isCoupleSeat(const char *seat) {
    return (seat[0] == 'E');
}

int isValidSeat(const char *seat) {
    if(strlen(seat) != 2) return 0;
    if(seat[0] < 'A' || seat[0] > 'E') return 0;
    if(seat[1] < '1' || seat[1] > '5') return 0;
    return 1;
}

/* Generate random pre-booked seats once per screening */
void generateRandomBooked(const char *screeningID) {
    if(strcmp(lastScreeningForRandom, screeningID) == 0) return;
    strcpy(lastScreeningForRandom, screeningID);
    randomBookedCount = 0;
    int used[ROWS][COLS];
    memset(used, 0, sizeof(used));
    int target = rand() % 4 + 3; /* 3-6 seats pre-booked */
    int tries = 0;
    while(randomBookedCount < target && tries < 200) {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if(!used[r][c]) {
            used[r][c] = 1;
            sprintf(randomBooked[randomBookedCount], "%c%d", 'A'+r, c+1);
            randomBookedCount++;
        }
        tries++;
    }
}

int isRandomBooked(const char *seat) {
    for(int i = 0; i < randomBookedCount; i++)
        if(strcmp(randomBooked[i], seat) == 0) return 1;
    return 0;
}

int seatBooked(const char *screeningID, const char *seat) {
    if(isRandomBooked(seat)) return 1;
    FILE *fp = fopen("data/tickets.csv", "r");
    if(!fp) return 0;
    Ticket t;
    while(fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                 t.ticketID, t.userID, t.screeningID, t.movieName,
                 t.showtime, t.seatCode, &t.price, &t.room) == 8) {
        if(strcmp(t.screeningID, screeningID) == 0 && strcmp(t.seatCode, seat) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void drawSeatMap(Vector2 mouse) {
    int seatW = 82, seatH = 60, padX = 10, padY = 12;
    int gridW = COLS * seatW + (COLS-1) * padX;  /* = 448 */
    int startX = (1280 - gridW) / 2;              /* = 416 */
    int startY = 165;

    /* Screen bar */
    DrawRectangleRounded((Rectangle){(float)(startX - 10), (float)(startY - 52),
                                     (float)(gridW + 20), 20}, 0.5f, 4,
                          (Color){160,160,255,160});
    DrawText("MAN HINH CHIEU",
             startX + gridW/2 - MeasureText("MAN HINH CHIEU", 15)/2,
             startY - 49, 15, (Color){30,30,80,255});

    for(int i = 0; i < ROWS; i++) {
        /* Row label */
        DrawText(TextFormat("%c", 'A'+i), startX - 28, startY + i*(seatH+padY) + 18, 22,
                 (Color){180,180,180,255});

        for(int j = 0; j < COLS; j++) {
            char code[10];
            sprintf(code, "%c%d", 'A'+i, j+1);

            Rectangle seat = {
                (float)(startX + j*(seatW+padX)),
                (float)(startY + i*(seatH+padY)),
                (float)seatW, (float)seatH
            };

            int booked   = seatBooked(screeningInput, code);
            int couple   = isCoupleSeat(code);
            int selected = (strcmp(seatInput, code) == 0);

            Color col;
            if(booked)        col = (Color){175, 30,  30,  255};
            else if(selected) col = (Color){ 40,185,  60,  255};
            else if(couple)   col = (Color){205,158,   0,  255};
            else              col = (Color){ 28, 58, 128,  255};

            /* Hover highlight (not for booked) */
            if(!booked && CheckCollisionPointRec(mouse, seat)) {
                col.r = col.r < 215 ? col.r + 40 : 255;
                col.g = col.g < 215 ? col.g + 40 : 255;
                col.b = col.b < 215 ? col.b + 40 : 255;
            }

            DrawRectangleRounded(seat, 0.2f, 6, col);

            /* Seat-back decoration (darker strip at top) */
            Color darkCol = {col.r > 30 ? col.r - 25 : 0,
                             col.g > 25 ? col.g - 25 : 0,
                             col.b > 25 ? col.b - 25 : 0, 255};
            DrawRectangleRounded((Rectangle){seat.x+6, seat.y, (float)(seatW-12), 13},
                                  0.3f, 4, darkCol);

            DrawText(code, (int)seat.x + (couple ? 18 : 25), (int)seat.y + 22, 20, WHITE);

            /* Couple marker */
            if(couple && !booked)
                DrawText("x2", (int)seat.x + 56, (int)seat.y + 43, 13,
                         (Color){255,240,140,255});

            if(CheckCollisionPointRec(mouse, seat) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if(!booked) { strcpy(seatInput, code); message[0] = '\0'; }
                else          strcpy(message, "Ghe nay da co nguoi dat!");
            }
        }
    }

    /* Column numbers */
    for(int j = 0; j < COLS; j++)
        DrawText(TextFormat("%d", j+1),
                 startX + j*(seatW+padX) + seatW/2 - 5,
                 startY + ROWS*(seatH+padY) + 4, 17, (Color){180,180,180,255});

    /* Legend (left side) */
    int lx = 30, ly = 430;
    DrawRectangleRounded((Rectangle){lx, ly,       130, 32}, 0.3f, 5, (Color){28,58,128,255});
    DrawText("Trong (40K)", lx+6, ly+9, 15, WHITE);

    DrawRectangleRounded((Rectangle){lx, ly+42,    130, 32}, 0.3f, 5, (Color){175,30,30,255});
    DrawText("Da dat",      lx+28, ly+51, 15, WHITE);

    DrawRectangleRounded((Rectangle){lx, ly+84,    130, 32}, 0.3f, 5, (Color){205,158,0,255});
    DrawText("Doi (80K)",   lx+12, ly+93, 15, WHITE);

    DrawRectangleRounded((Rectangle){lx, ly+126,   130, 32}, 0.3f, 5, (Color){40,185,60,255});
    DrawText("Dang chon",   lx+10, ly+135, 15, WHITE);
}