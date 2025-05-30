/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

static bool is_a_flag(const char *str)
{
    return strcmp(str, "-p") == 0 || strcmp(str, "-x") == 0 ||
        strcmp(str, "-y") == 0 || strcmp(str, "-n") == 0 ||
        strcmp(str, "-c") == 0 || strcmp(str, "-f") == 0;
}

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
