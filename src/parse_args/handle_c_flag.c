/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

zap_srv_flags_t handle_c_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    size_t max_clients = get_size_t_from_str(av[(*i) + 1]);

    ctxt->max_clients_per_team = max_clients;
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        tmp->max_clients = max_clients;
    }
    *i += 2;
    return ZAP_SRV_FLAG_C;
}
