/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** hatch_team
*/

#include "egg_internal.h"

/**
 * @brief Finds a team in the parsed context by its name.
 *
 * Iterates through the list of teams in the given context and returns a
 * pointer to the team structure whose name matches the provided team name.
 *
 * @param ctxt Pointer to the parsed context containing the list of teams.
 * @param team The name of the team to search for.
 * @return Pointer to the matching zap_srv_team_t structure if found, NULL
 * otherwise.
 */
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

/**
 * @brief Removes a specified egg node from a linked list of eggs.
 *
 * This function searches for the given egg node (`tmp`) in the linked list
 * pointed to by `list` and removes it from the list. If the node to be removed
 * is the head of the list, the head pointer is updated. The memory for the
 * removed node is freed using `safe_free`.
 *
 * @param list Double pointer to the head of the linked list of eggs.
 * @param tmp Pointer to the egg node to be removed from the list.
 */
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

/**
 * @brief Hatches a random egg from the specified team.
 *
 * This function selects a random egg from the given team's egg list and
 * removes it, simulating the hatching of the egg. If the team is not found,
 * the function returns immediately. The selection is based on a random index
 * within the maximum number of eggs.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param team Name of the team whose egg should be hatched.
 */
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
