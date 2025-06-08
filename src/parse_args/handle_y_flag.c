/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

/**
 * @brief Handles the '-y' flag from the command-line arguments, which
 * specifies the height (y-dimension) of the map for the Zappy server.
 *
 * This function parses the value following the '-y' flag, converts it to a
 * size_t, and updates the map height in the provided context structure.
 * It also advances the argument index accordingly.
 *
 * @param av The array of command-line argument strings.
 * @param ctxt Pointer to the parsed context structure to update.
 * @param i Pointer to the current index in the argument array; will be
 * incremented by 2 to skip the flag and its value.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if the value is invalid
 * (via get_size_t_from_str).
 *
 * @return ZAP_SRV_FLAG_Y to indicate the '-y' flag was handled.
 */
zap_srv_flags_t handle_y_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    size_t y = get_size_t_from_str(av[(*i) + 1]);

    if (y > SSIZE_MAX || y < 10) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    ctxt->map.y = (ssize_t)y;
    *i += 2;
    return ZAP_SRV_FLAG_Y;
}
