/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** eject
*/

#include "actions.h"

/**
 * @brief Pushes a client to a new position on the map based on the given
 * orientation, updates the client's position, notifies the client of the
 * ejection, and sends the updated player position to all relevant parties.
 *
 * @param ctxt Pointer to the parsed server context containing map information.
 * @param client Pointer to the player/client to be pushed.
 * @param orientation The direction in which the client is being pushed.
 * @param new_orientation The orientation to notify the client about after
 * being pushed.
 */
static void push_client(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, zap_srv_player_orientation_t orientation,
    zap_srv_player_orientation_t new_orientation)
{
    char *block;
    zap_srv_pos_t map_size = (zap_srv_pos_t){ctxt->map.x, ctxt->map.y};
    zap_srv_pos_t new_pos =
        compute_next_position(&client->pos, orientation, &map_size);

    client->pos.x = new_pos.x;
    client->pos.y = new_pos.y;
    block = snprintf_alloc("eject: %d\n", new_orientation);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
    send_ppo(ctxt, client);
}

/**
 * @brief Ejects all players from the same position as the given client, except
 * the client itself and graphic clients.
 *
 * This function iterates through all connected clients and checks if they are
 * on the same position as the specified client. If a client is not a graphic
 * client, is not the same as the specified client, and shares the same
 * position, it will be pushed in the direction of the specified client's
 * orientation.
 *
 * @param ctxt Pointer to the parsed server context containing all clients.
 * @param client Pointer to the client initiating the eject action.
 */
static void eject_players(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    zap_srv_player_orientation_t orientation =
        ((client->orientation + 1) % 4) + 1;

    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        if (ctxt->server.clients[i].team &&
            strcmp("GRAPHIC", ctxt->server.clients[i].team) != 0 &&
            ctxt->server.clients[i].id != client->id &&
            ctxt->server.clients[i].pos.x == client->pos.x &&
            ctxt->server.clients[i].pos.y == client->pos.y) {
            push_client(ctxt, &(ctxt->server.clients[i]), client->orientation,
                orientation);
        }
    }
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

    if (!list || !*list || !tmp) {
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
 * @brief Checks if the given egg is at the same position as the client and
 * removes it if so.
 *
 * This function compares the position of the specified egg with the position
 * of the given client. If both positions match, it sends an EDI (egg deletion
 * information) message and removes the egg from the provided egg list.
 *
 * @param ctxt   Pointer to the parsed server context.
 * @param list   Double pointer to the list of eggs.
 * @param egg    Pointer to the egg to check and potentially remove.
 * @param client Pointer to the player (client) whose position is compared.
 */
static void check_remove_egg(zap_srv_parsed_context_t *ctxt,
    zap_srv_egg_t **list, zap_srv_egg_t *egg, zap_srv_player_t *client)
{
    if (egg->pos.x != client->pos.x || egg->pos.y != client->pos.y) {
        return;
    }
    send_edi(ctxt, egg);
    remove_egg(list, egg);
}

/**
 * @brief Ejects eggs belonging to all teams in the context that are associated
 * with the specified player.
 *
 * Iterates through all teams in the given context, and for each team's egg
 * list, checks and removes eggs that are associated with the specified
 * client/player.
 *
 * @param ctxt   Pointer to the parsed server context containing teams and
 * their eggs.
 * @param client Pointer to the player for whom associated eggs should be
 * checked and potentially removed.
 */
static void eject_eggs(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    zap_srv_egg_t *egg_list;

    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        egg_list = tmp->eggs;
        for (zap_srv_egg_t *tmp2 = egg_list; tmp2; tmp2 = tmp2->next) {
            check_remove_egg(ctxt, &egg_list, tmp2, client);
        }
    }
}

/**
 * @brief Handles the eject action for a player.
 *
 * This function performs the eject action initiated by the specified player.
 * It ejects other players and eggs from the player's current location,
 * then sends an "ok" response to the client.
 *
 * @param ctxt Pointer to the server's parsed context structure.
 * @param client Pointer to the player initiating the eject action.
 * @param arguments Unused parameter for additional arguments.
 * @return true Always returns true to indicate the action was processed.
 */
bool player_eject(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED const char *arguments)
{
    eject_players(ctxt, client);
    eject_eggs(ctxt, client);
    send_client("ok\n", &client->sock);
    return true;
}
