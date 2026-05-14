#include "models/ticket.h"
#include "../project/globals.h"
#include "models/showtime.h"
#include "../utils/seat_utils.h"
#include <stdio.h>
#include <stdlib.h> // For rand()
#include <string.h>

void generateTicketID(char *id) {
    sprintf(id, "TICKET_%06d", rand() % 1000000);
}

/* ===== UC11 – BUY TICKET ===== */
void buyTicket() {
    if(!strlen(screeningInput)) { strcpy(message, "Chua nhap ID suat chieu!"); return; }
    if(!isValidSeat(seatInput))  { strcpy(message, "Ma ghe khong hop le!"); return; }
    if(seatBooked(screeningInput, seatInput)) { strcpy(message, "Ghe nay da co nguoi dat!"); return; }

    Ticket t;
    generateTicketID(t.ticketID);
    strcpy(t.userID,      currentUserID);
    strcpy(t.screeningID, screeningInput);
    strcpy(t.seatCode,    seatInput);
    strcpy(t.movieName,   "Unknown");
    strcpy(t.showtime,    "00:00");

    for(int i = 0; i < showtimeCount; i++) {
        if(strcmp(showtimes[i].id, screeningInput) == 0) {
            strcpy(t.movieName, showtimes[i].movie);
            strcpy(t.showtime,  showtimes[i].time);
            break;
        }
    }

    t.price = isCoupleSeat(seatInput) ? 80000 : 40000;
    if(buyWater)   t.price += 20000;
    if(buyPopcorn) t.price += 20000;
    t.room = 1;

    FILE *fp = fopen("data/tickets.csv", "a");
    if(!fp) { strcpy(message, "Khong mo duoc file!"); return; }
    fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d\n",
            t.ticketID, t.userID, t.screeningID, t.movieName,
            t.showtime, t.seatCode, t.price, t.room);
    fclose(fp);

    sprintf(message, "Dat ve thanh cong!  %s", t.ticketID);
    buyWater = 0; // Reset after purchase
    buyPopcorn = 0; // Reset after purchase
    seatInput[0] = '\0'; // Clear selected seat
    screeningInput[0] = '\0'; // Clear selected screening
}

/* ===== UC12 – CANCEL TICKET ===== */
void cancelTicket() {
    FILE *fp = fopen("data/tickets.csv", "r");
    if(!fp) { strcpy(message, "Khong mo duoc file!"); return; }
    FILE *tmp = fopen("data/temp.csv", "w");
    if(!tmp) { fclose(fp); strcpy(message, "Loi he thong!"); return; }

    Ticket t;
    int found = 0;
    while(fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                 t.ticketID, t.userID, t.screeningID, t.movieName,
                 t.showtime, t.seatCode, &t.price, &t.room) == 8) {
        if(strcmp(t.ticketID, cancelInput) == 0) {
            found = 1;
            if(strcmp(t.userID, currentUserID) != 0) {
                strcpy(message, "Ban khong co quyen huy ve nay!");
                fclose(fp); fclose(tmp); remove("data/temp.csv");
                return;
            }
            continue; /* skip = cancel this ticket */
        }
        fprintf(tmp, "%s,%s,%s,%s,%s,%s,%d,%d\n",
                t.ticketID, t.userID, t.screeningID, t.movieName,
                t.showtime, t.seatCode, t.price, t.room);
    }
    fclose(fp); fclose(tmp);
    remove("data/tickets.csv");
    rename("data/temp.csv", "data/tickets.csv");

    if(found) { strcpy(message, "Huy ve thanh cong!"); cancelInput[0] = '\0'; }
    else       strcpy(message, "Khong tim thay ma ve!");
}