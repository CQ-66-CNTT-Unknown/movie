#pragma once

#include "../models/user.h"

/**
 *@brief Show the actions menu based on the user's role
 *@param role The role of the user (MANAGER or CUSTOMER)
 */
void show_actions_menu(UserRole role);