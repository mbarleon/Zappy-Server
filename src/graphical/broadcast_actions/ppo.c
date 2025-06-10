/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** ppo
*/

#include "../graphical_internal.h"

/**
 * @brief Sends the player's position and orientation to all graphical clients.
 *
 * This function formats and broadcasts the "ppo" command, which includes the
 * player's unique ID, x and y coordinates, and orientation. The message is
 * sent to all connected graphical clients using the provided context.
 *
 * @param ctxt Pointer to the parsed server context containing graphical client
 * information.
 * @param client Pointer to the player whose position and orientation will be
 * broadcasted.
 */
void send_ppo(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("ppo #%ld %ld %ld %d\n", client->id, client->pos.x,
        client->pos.y, client->orientation);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
