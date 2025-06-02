/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** get_size_t_from_str
*/

#include "parse_args_internal.h"

/**
 * @brief Converts a string to a size_t value.
 *
 * Parses the input string as an unsigned integer and returns its value as
 * size_t.
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if:
 *   - The input string is NULL,
 *   - The string does not represent a valid number,
 *   - The value is out of range for size_t,
 *   - The string contains extra characters after the number.
 *
 * @param str The string to convert.
 *
 * @return The converted size_t value.
 */
size_t get_size_t_from_str(const char *str)
{
    char *endptr = NULL;
    unsigned long long val = 0;

    if (!str) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    errno = 0;
    val = strtoull(str, &endptr, 10);
    if (errno == ERANGE || errno == EINVAL || val > SIZE_MAX ||
        endptr == str || *endptr != '\0') {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    return (size_t)val;
}

/**
 * @brief Converts a string to a uint16_t value.
 *
 * Parses the input string as an unsigned integer and returns its value as
 * uint16_t.
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if:
 *   - The input string is NULL,
 *   - The string does not represent a valid number,
 *   - The value is out of range for uint16_t,
 *   - The string contains extra characters after the number.
 *
 * @param str The string to convert.
 *
 * @return The converted uint16_t value.
 */
uint16_t get_uint16_from_str(const char *str)
{
    char *endptr = NULL;
    unsigned long val = 0;

    if (!str) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    errno = 0;
    val = strtoul(str, &endptr, 10);
    if (errno == ERANGE || errno == EINVAL || val > UINT16_MAX ||
        endptr == str || *endptr != '\0') {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    return (uint16_t)val;
}
