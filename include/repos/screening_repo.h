#pragma once

#include "../models/screening.h"

#include <stdio.h>

/**
 * @brief Get all screenings from the system
 * @param screening_source_path The file path for screenings
 * @return pointer to ScreeningArray containing all screenings or `NULL` if an error occurs
 */
ScreeningArray *get_all_screenings(const char *screening_source_path);
