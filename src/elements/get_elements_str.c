/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** get_elements_str
*/

#include "elements.h"
#include <strings.h>

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
        case UNKNOWN_ELEMENT:
            return "unknown";
        default:
            return "unknown";
    }
}

/**
 * @brief Converts a string representation of an element to its corresponding
 * zap_srv_elements_t enum value.
 *
 * This function compares the input string (case-insensitive) to known element
 * names ("FOOD", "LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS",
 * "THYSTAME") and returns the corresponding enum value. If the string does not
 * match any known element or is NULL, UNKNOWN_ELEMENT is returned.
 *
 * @param str The string representation of the element (case-insensitive).
 * @return zap_srv_elements_t The corresponding enum value, or UNKNOWN_ELEMENT
 * if not found.
 */
zap_srv_elements_t get_element_from_str(const char *str)
{
    if (!str)
        return UNKNOWN_ELEMENT;
    if (strcasecmp(str, "FOOD") == 0)
        return FOOD;
    if (strcasecmp(str, "LINEMATE") == 0)
        return LINEMATE;
    if (strcasecmp(str, "DERAUMERE") == 0)
        return DERAUMERE;
    if (strcasecmp(str, "SIBUR") == 0)
        return SIBUR;
    if (strcasecmp(str, "MENDIANE") == 0)
        return MENDIANE;
    if (strcasecmp(str, "PHIRAS") == 0)
        return PHIRAS;
    if (strcasecmp(str, "THYSTAME") == 0)
        return THYSTAME;
    return UNKNOWN_ELEMENT;
}
