#pragma once

/**
 * @brief Enum representing the role of a user
 */
typedef enum UserRole { MANAGER, CUSTOMER } UserRole;

/**
 * @brief User structure representing a user in the system
 */
typedef struct User {
    int user_id; /**< The unique identifier for the user */
    char username[50]; /**< The username of the user */
    UserRole role; /**< The role of the user */
} User;
