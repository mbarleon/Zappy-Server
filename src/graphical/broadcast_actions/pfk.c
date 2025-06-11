/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pfk
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "pfk" (player fork) message to all graphical clients.
 *
 * This function formats and broadcasts a message indicating that the specified
 * player has initiated a fork action. The message is sent to all connected
 * graphical clients using the provided context.
 *
 * @param ctxt Pointer to the parsed server context used for broadcasting.
 * @param client Pointer to the player structure representing the forking
 * player.
 */
void send_pfk(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("pfk #%ld\n", client->id);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
