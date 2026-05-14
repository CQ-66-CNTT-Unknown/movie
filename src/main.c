#include <stdio.h>
#include <unistd.h>
#include "../include/services/auth.h"
#include "../include/utils/menu.h"

int main() {
    printf("Welcome to our cinema ticket booking system!\n");
    // User user = login();

    // Mocking action
    User user = {3, "TTNguyen2505", MANAGER};
    show_actions_menu(user.role);
    
    // Delay 5 seconds to show the menu
    sleep(5);
    return 0;
}
