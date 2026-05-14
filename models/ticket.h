#ifndef TICKET_H
#define TICKET_H
typedef struct {
    char ticketID[30];
    char userID[30];
    char screeningID[30];
    char movieName[100];
    char showtime[30];
    char seatCode[10];
    int price;
    int room;
} Ticket;
void buyTicket();
void cancelTicket();
#endif