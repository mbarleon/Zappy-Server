/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** get_size_t_from_str
*/

#include "parse_args_internal.h"

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
