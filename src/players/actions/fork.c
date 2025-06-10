/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** fork
*/

#include "actions.h"

/**
 * @brief Handles the "fork" action for a player, creating a new egg for the
 * player's team.
 *
 * This function is called when a player requests to "fork", which in the
 * context of the game, typically means spawning a new egg (potential future
 * player) for their team. The function:
 *   - Finds the player's team in the context.
 *   - Increments the team's available slots.
 *   - Adds a new egg at the player's current position with the player's ID as
 *     the parent.
 *   - Notifies the client of success or failure.
 *   - Sends an "enw" event to notify the rest of the system about the new egg.
 *
 * @param ctxt Pointer to the parsed server context containing teams and
 * game state.
 * @param client   Pointer to the player structure requesting the fork.
 * @param arguments Unused parameter for additional command arguments.
 */
bool player_fork(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED const char *arguments)
{
    zap_srv_egg_t **egg_list = NULL;

    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, client->team) == 0) {
            egg_list = &tmp->eggs;
            tmp->available_slots += 1;
        }
    }
    if (!egg_list) {
        send_client("ko\n", &client->sock);
        return false;
    }
    add_egg(egg_list, &client->pos, client->id);
    send_client("ok\n", &client->sock);
    send_pfk(ctxt, client);
    send_enw(ctxt, *egg_list);
    return true;
}
