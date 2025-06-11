/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "player died" (pdi) message to all graphical clients.
 *
 * This function constructs a message indicating that the specified player has
 * died, and broadcasts it to all connected graphical clients using the
 * provided context.
 *
 * @param ctxt Pointer to the parsed server context used for broadcasting.
 * @param client Pointer to the player structure representing the player who
 * died.
 */
void send_pdi(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("pdi #%ld\n", client->id);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
