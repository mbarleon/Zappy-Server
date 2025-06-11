/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "pgt" (player gets resource) message to all graphical
 * clients.
 *
 * This function formats and broadcasts a message indicating that a player has
 * picked up a specific element/resource. The message is sent to all connected
 * graphical clients for real-time updates.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player who picked up the element.
 * @param element The element/resource that was picked up by the player.
 */
void send_pgt(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_elements_t element)
{
    char *block;

    block = snprintf_alloc("pgt #%ld %d\n", client->id, element);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
