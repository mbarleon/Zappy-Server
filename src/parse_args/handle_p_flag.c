/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

/**
 * @brief Handles the '-p' flag from the command-line arguments, which s
 * pecifies the server port.
 *
 * This function parses the port number from the argument vector at the
 * position following the '-p' flag, updates the server context with the parsed
 * port, and advances the argument index accordingly.
 *
 * @param av The array of command-line argument strings.
 * @param ctxt Pointer to the server parsed context structure to update with
 * the port value.
 * @param i Pointer to the current index in the argument array; will be
 * incremented by 2.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if the value is invalid
 * (via get_uint16_from_str).
 *
 * @return ZAP_SRV_FLAG_P to indicate the '-p' flag was handled.
 */
zap_srv_flags_t handle_p_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    uint16_t port = get_uint16_from_str(av[(*i) + 1]);

    ctxt->server.port = port;
    *i += 2;
    return ZAP_SRV_FLAG_P;
}
