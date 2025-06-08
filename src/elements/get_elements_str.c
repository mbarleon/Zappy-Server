/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** get_elements_str
*/

#include "elements.h"

/**
 * @brief Returns the string representation of a zap_srv_elements_t enum value.
 *
 * This function maps each zap_srv_elements_t element to its corresponding
 * string name. If the provided element does not match any known value,
 * "unknown" is returned.
 *
 * @param element The zap_srv_elements_t enum value to convert.
 * @return The string representation of the element, or "unknown" if not
 * recognized.
 */
const char *get_elements_str(zap_srv_elements_t element)
{
    switch (element) {
        case FOOD:
            return "food";
        case LINEMATE:
            return "linemate";
        case DERAUMERE:
            return "deraumere";
        case SIBUR:
            return "sibur";
        case MENDIANE:
            return "mendiane";
        case PHIRAS:
            return "phiras";
        case THYSTAME:
            return "thystame";
        default:
            return "unknown";
    }
}
