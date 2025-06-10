/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Handles the "sst" graphical command to set the server frequency.
 *
 * This function updates the server's frequency based on the provided
 * arguments, formats a response message, and broadcasts it to all connected
 * graphical clients.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client UNUSED. Pointer to the player/client structure (not used in
 * this function).
 * @param args Pointer to the structure containing graphical command arguments.
 */
void graph_sst(zap_srv_parsed_context_t *ctxt, UNUSED zap_srv_player_t *client,
    zap_srv_graph_args_t *args)
{
    char *block;

    ctxt->server.frequency = args->size_a;
    block = snprintf_alloc("sst %ld\n", ctxt->server.frequency);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
