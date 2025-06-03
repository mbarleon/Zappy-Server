/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

/**
 * @brief Checks if the given string is a recognized command-line flag.
 *
 * @param str The string to check.
 *
 * @return true if the string matches one of the known flags
 * ("-p", "-x", "-y", "-n", "-c", "-f"), false otherwise.
 */
static bool is_a_flag(const char *str)
{
    return strcmp(str, "-p") == 0 || strcmp(str, "-x") == 0 ||
        strcmp(str, "-y") == 0 || strcmp(str, "-n") == 0 ||
        strcmp(str, "-c") == 0 || strcmp(str, "-f") == 0;
}

/**
 * @brief Handles the "-n" flag in the command-line arguments, adding team
 * names to the context.
 *
 * Iterates through the arguments following the "-n" flag, creating a team
 * for each argument until another flag or the end of the argument list is
 * encountered. Updates the index accordingly.
 *
 * @param av The array of command-line argument strings.
 * @param ctxt The context structure where teams are stored.
 * @param i Pointer to the current index in the argument array; will be updated
 * as teams are added.
 *
 * @throws CEXTEND_EXCEPTION_BAD_ALLOC if memory allocation fails
 * (via safe_calloc or safe_strdup).
 *
 * @return ZAP_SRV_FLAG_N to indicate the "-n" flag was processed.
 */
zap_srv_flags_t handle_n_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    while (!is_a_flag(av[(*i + 1)]) && av[(*i + 1)]) {
        create_team(&ctxt->teams, av[(*i + 1)], ctxt->max_clients_per_team);
        *i += 1;
    }
    *i += 1;
    return ZAP_SRV_FLAG_N;
}
