/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the position and orientation of a player to the graphical
 * client.
 *
 * This function formats and sends a message containing the player's ID,
 * position (x, y), and orientation to the graphical client. The message
 * follows the format: "ppo #<id> <x> <y> <orientation>\n".
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player whose information is to be sent.
 * @param args Pointer to additional graphical arguments, including the player
 * list size.
 */
void graph_ppo(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args)
{
    char *block;
    size_t i = find_player_index(ctxt, client, args->ssize_a);

    if (i == SIZE_MAX) {
        return;
    }
    block = snprintf_alloc("ppo #%ld %ld %ld %d\n", ctxt->server.clients[i].id,
        ctxt->server.clients[i].pos.x, ctxt->server.clients[i].pos.x,
        ctxt->server.clients[i].orientation);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}
