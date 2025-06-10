/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "pie" (player incantation end) message to all graphical
 * clients.
 *
 * This function formats and broadcasts a message indicating the result of a
 * player incantation at a specific position on the map. The message is sent to
 * all connected graphical clients.
 *
 * @param ctxt   Pointer to the parsed server context.
 * @param client Pointer to the player structure, containing position
 * information.
 * @param worked Boolean indicating if the incantation succeeded (true for
 * "ok", false for "ko").
 */
void send_pie(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    bool worked)
{
    char *block;

    block = snprintf_alloc("pie %ld %ld %s\n", client->pos.x,
        client->pos.y, worked ? "ok" : "ko");
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
        block = NULL;
    }
}
