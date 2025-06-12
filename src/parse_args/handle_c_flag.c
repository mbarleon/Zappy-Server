/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

/**
 * @brief Handles the '-c' flag for setting the maximum number of clients per
 * team.
 *
 * This function parses the maximum number of clients from the command-line
 * arguments, updates the parsed context with this value, and applies it to all
 * teams in the context. It also advances the argument index accordingly.
 *
 * @param av The array of command-line argument strings.
 * @param ctxt Pointer to the parsed context structure to update.
 * @param i Pointer to the current index in the argument array; will be
 * incremented by 2.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if the value is invalid
 * (via get_size_t_from_str).
 *
 * @return ZAP_SRV_FLAG_C to indicate the '-c' flag was handled.
 */
zap_srv_flags_t handle_c_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    size_t max_clients = get_size_t_from_str(av[(*i) + 1]);

    if (max_clients == 0) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    ctxt->max_clients_per_team = max_clients;
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        tmp->max_clients = max_clients;
    }
    *i += 2;
    return ZAP_SRV_FLAG_C;
}
