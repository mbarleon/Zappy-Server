/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

/**
 * @brief Handles the '-x' flag from the command-line arguments, which sets the
 * map width.
 *
 * This function parses the next argument as a size_t value representing the
 * map's width, updates the context structure with this value, and advances the
 * argument index accordingly.
 *
 * @param av The array of command-line argument strings.
 * @param ctxt Pointer to the parsed context structure to update the map width.
 * @param i Pointer to the current index in the argument array; will be
 * incremented by 2.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if the value is invalid
 * (via get_size_t_from_str).
 *
 * @return ZAP_SRV_FLAG_X to indicate the '-x' flag was handled.
 */
zap_srv_flags_t handle_x_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    size_t x = get_size_t_from_str(av[(*i) + 1]);

    ctxt->map.x = x;
    *i += 2;
    return ZAP_SRV_FLAG_X;
}
