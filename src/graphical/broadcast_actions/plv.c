/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends the player's level information to all graphical clients.
 *
 * Constructs a message containing the player's ID and level in the format
 * "plv #<id> <level>\n" and broadcasts it to all connected graphical clients.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player whose level information will be sent.
 */
void send_plv(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("plv #%ld %ld\n", client->id, client->level);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
