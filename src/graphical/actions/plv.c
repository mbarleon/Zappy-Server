/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the level of a specified player to all graphical clients.
 *
 * This function locates the player in the server's client list using the
 * provided context and arguments. If the player is found, it formats a message
 * containing the player's ID and level, then send this message to the client.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player whose level is being requested.
 * @param args Pointer to additional arguments required for the operation.
 */
void graph_plv(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args)
{
    char *block;
    size_t i = find_player_index(ctxt, client, args->ssize_a);

    if (i == SIZE_MAX) {
        return;
    }
    block = snprintf_alloc("plv #%ld %ld\n", ctxt->server.clients[i].id,
        ctxt->server.clients[i].level);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}
