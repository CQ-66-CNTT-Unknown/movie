#pragma once

#include "../models/user.h"

/**
 * @brief Log in a user with the given username and password, the function ends until the user successfully logs in
 * @return The logged-in user
 */
User login();

/**
 * @brief Authenticate a user with username and password
 * @param username The username of the user
 * @param password The password of the user
 * @return User structure if login successful (user_id > 0), otherwise invalid user
 */
User login_user(const char *username, const char *password);