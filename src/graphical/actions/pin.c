/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the inventory information of a specific player to all graphical
 * clients.
 *
 * This function locates the player specified by the arguments, formats their
 * inventory and position into a protocol-compliant string, and broadcasts it
 * to all connected graphical clients. If the player is not found, the function
 * returns without action.
 *
 * @param ctxt Pointer to the server context containing client and server
 * state.
 * @param client Pointer to the player client requesting the action.
 * @param args Pointer to the structure containing parsed arguments for the
 * action.
 */
void graph_pin(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args)
{
    char *block;
    size_t i = find_player_index(ctxt, client, args->ssize_a);

    if (i == SIZE_MAX) {
        return;
    }
    block = snprintf_alloc("pin #%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        ctxt->server.clients[i].id, ctxt->server.clients[i].pos.x,
        ctxt->server.clients[i].pos.y, ctxt->server.clients[i].inventory[FOOD],
        ctxt->server.clients[i].inventory[LINEMATE],
        ctxt->server.clients[i].inventory[DERAUMERE],
        ctxt->server.clients[i].inventory[SIBUR],
        ctxt->server.clients[i].inventory[MENDIANE],
        ctxt->server.clients[i].inventory[PHIRAS],
        ctxt->server.clients[i].inventory[THYSTAME]);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}
