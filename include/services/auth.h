#pragma once

#include "../models/user.h"

/**
 * @brief Log in a user with the given username and password, the function ends until the user successfully logs in
 * @return The logged-in user
 */
User login();