/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "pdr" (player drop resource) message to all graphical
 * clients.
 *
 * This function formats and broadcasts a message indicating that a player has
 * dropped a specific resource element. The message is sent to all connected
 * graphical clients.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player (client) who dropped the resource.
 * @param element The resource element that was dropped.
 */
void send_pdr(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_elements_t element)
{
    char *block;

    block = snprintf_alloc("pdr #%ld %d\n", client->id, element);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
