/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** hatch_team
*/

#include "egg_internal.h"

static zap_srv_team_t *find_team(zap_srv_parsed_context_t *ctxt,
    const char *team)
{
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(team, tmp->name) == 0) {
            return tmp;
        }
    }
    return NULL;
}

static void remove_egg(zap_srv_egg_t **list, zap_srv_egg_t *tmp)
{
    zap_srv_egg_t *tmp2;

    if (!list || !*list || tmp) {
        return;
    }
    if (tmp == *list) {
        *list = (*list)->next;
        safe_free((void **)&tmp);
        return;
    }
    for (tmp2 = *list; tmp2; tmp2 = tmp2->next) {
        if (tmp2->next == tmp) {
            tmp2->next = tmp->next;
            safe_free((void **)&tmp);
            return;
        }
    }
}

void hatch_egg(zap_srv_parsed_context_t *ctxt, const char *team)
{
    zap_srv_team_t *my_team = find_team(ctxt, team);
    size_t egg_index = (size_t)rand() % ZAP_SRV_EGG_MAX;

    if (!my_team) {
        return;
    }
    for (zap_srv_egg_t *tmp = my_team->eggs; tmp; tmp = tmp->next) {
        egg_index--;
        if (egg_index == 0) {
            remove_egg(&my_team->eggs, tmp);
            return;
        }
        if (!tmp->next) {
            tmp = my_team->eggs;
        }
    }
}
