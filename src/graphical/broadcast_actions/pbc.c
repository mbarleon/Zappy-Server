/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a broadcast message to all graphical clients in the Zappy
 * server.
 *
 * This function formats a broadcast message using the player's ID and the
 * provided message, then sends it to all connected graphical clients. The
 * message is formatted as: "pbc #<player_id> <message>\n".
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player structure representing the client
 * sending the message.
 * @param msg The message to broadcast.
 */
void send_pbc(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *msg)
{
    char *block;

    block = snprintf_alloc("pbc #%ld %s\n", client->id, msg);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
