/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** enw
*/

#include "../graphical_internal.h"

/**
 * @brief Sends an "enw" (egg new) message to all graphical clients.
 *
 * This function formats and broadcasts an "enw" message, which notifies
 * graphical clients about the creation of a new egg in the game. The message
 * includes the egg's unique number, the number of the player who laid the egg,
 * and the egg's position (x, y) on the map.
 *
 * @param ctxt Pointer to the parsed server context, used for broadcasting.
 * @param egg Pointer to the egg structure containing egg details.
 */
void send_enw(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg)
{
    char *block;

    block = snprintf_alloc("enw #%ld #%ld %ld %ld\n", egg->number,
        egg->player_number, egg->pos.x, egg->pos.y);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
