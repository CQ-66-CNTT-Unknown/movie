#include "../../include/utils/menu.h"
#include <stdio.h>

void show_manager_actions_menu() {
    printf("Manager Actions Menu:\n");
    printf("1. Add Movie\n");
    printf("2. Edit Movie\n");
    printf("3. Delete Movie\n");
    printf("4. View Screenings\n");
    printf("5. Create Screening\n");
    printf("6. Cancel Screening\n");
    printf("7. Show Revenue Report\n");
    printf("8. Logout\n");
    printf("Please select an action: ");
}

void show_customer_actions_menu() {
    printf("Customer Actions Menu:\n");
    printf("1. View Movies\n");
    printf("2. Search Movies\n");
    printf("3. Show seat map\n");
    printf("4. Book Ticket\n");
    printf("5. Cancel Ticket\n");
    printf("6. View Purchase History\n");
    printf("7. Logout\n");
    printf("Please select an action: ");
}

void show_actions_menu(UserRole role) {
    if (role == MANAGER)
        show_manager_actions_menu();
    else
        show_customer_actions_menu();
}
