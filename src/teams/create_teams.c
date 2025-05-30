/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** create_teams
*/

#include "teams_internal.h"

void create_team(zap_srv_team_t **teams, const char *str, size_t max_clients)
{
    zap_srv_team_t *tmp;
    zap_srv_team_t *new_team;

    if (!teams || strcmp(str, "GRAPHIC") == 0) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    new_team = safe_malloc(sizeof(zap_srv_team_t), NULL);
    new_team->next = NULL;
    new_team->num_clients = 0;
    new_team->name = safe_strdup(str);
    new_team->max_clients = max_clients;
    if (!*teams) {
        *teams = new_team;
        return;
    }
    for (tmp = *teams; tmp->next; tmp = tmp->next);
    if (!tmp) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    tmp->next = new_team;
}
