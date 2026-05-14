#include "../../include/models/user.h"
#include "../../include/utils/csv_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100

/**
 * @brief Internal function to load users from CSV file
 * @param users Array to store loaded users
 * @return Number of users loaded
 */
static int load_users_from_csv(User users[]) {
    FILE *file = fopen("data/user.csv", "r");
    if (file == NULL) {
        return 0;
    }

    char line[256];
    int user_count = 0;

    // Skip header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && user_count < MAX_USERS) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;

        char *fields[4];
        parse_csv_line(line, fields, 4);

        users[user_count].user_id = atoi(fields[0]);
        strcpy(users[user_count].username, fields[1]);
        users[user_count].role = atoi(fields[3]);

        user_count++;
    }

    fclose(file);
    return user_count;
}

/**
 * @brief Verify password from CSV
 * @param username Username to verify
 * @param password Password to verify
 * @return 1 if valid, 0 otherwise
 */
static int verify_password(const char *username, const char *password) {
    FILE *file = fopen("data/user.csv", "r");
    if (file == NULL) {
        return 0;
    }

    char line[256];
    
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *fields[4];
        parse_csv_line(line, fields, 4);

        if (strcmp(fields[1], username) == 0) {
            if (strcmp(fields[2], password) == 0) {
                fclose(file);
                return 1;
            }
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 0;
}

User login_user(const char *username, const char *password) {
    User invalid_user = {0, "", CUSTOMER};

    // Verify credentials
    if (!verify_password(username, password)) {
        return invalid_user;
    }

    // Load users to find the user info
    User users[MAX_USERS];
    int user_count = load_users_from_csv(users);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return users[i];
        }
    }

    return invalid_user;
}
