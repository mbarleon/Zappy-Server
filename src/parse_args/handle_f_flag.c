/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

/**
 * @brief Handles the '-f' flag for setting the server frequency.
 *
 * This function parses the frequency value from the command-line arguments,
 * updates the server context with the new frequency, and advances the argument
 * index.
 *
 * @param av The array of command-line argument strings.
 * @param ctxt Pointer to the server parsed context structure to update.
 * @param i Pointer to the current index in the argument array; will be
 * incremented by 2.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if the value is invalid
 * (via get_size_t_from_str).
 *
 * @return ZAP_SRV_FLAG_F to indicate the '-f' flag was handled.
 */
zap_srv_flags_t handle_f_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    size_t frequency = get_size_t_from_str(av[(*i) + 1]);

    if (frequency == 0) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    ctxt->server.frequency = frequency * 100UL;
    *i += 2;
    return ZAP_SRV_FLAG_F;
}
