/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

static void create_team(zap_srv_parsed_context_t *ctxt, const char *str)
{
    zap_srv_team_t *tmp;
    zap_srv_team_t *new_team = safe_malloc(sizeof(zap_srv_team_t), NULL);

    new_team->next = NULL;
    new_team->num_clients = 0;
    new_team->name = safe_strdup(str);
    new_team->max_clients = ctxt->max_clients_per_team;
    if (!ctxt->teams) {
        ctxt->teams = new_team;
        return;
    }
    for (tmp = ctxt->teams; tmp->next; tmp = tmp->next);
    tmp->next = new_team;
}

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
        create_team(ctxt, av[(*i + 1)]);
        *i += 1;
    }
    *i += 1;
    return ZAP_SRV_FLAG_N;
}
