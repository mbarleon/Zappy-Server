/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** is_valid_char
*/

#include "utils.h"

/**
 * @brief Checks if a character is valid for input processing.
 *
 * A character is considered valid if it is a newline ('\n'), a tab ('\t'),
 * or any printable ASCII character (from space ' ' (32) to tilde '~' (126)).
 *
 * @param c The character to validate.
 * @return Non-zero if the character is valid, 0 otherwise.
 */
bool is_valid_char(char c)
{
    return c != '%' && (c == '\n' || c == '\t' || (c >= 32 && c <= 126));
}
