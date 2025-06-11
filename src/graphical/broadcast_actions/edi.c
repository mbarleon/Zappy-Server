/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** enw
*/

#include "../graphical_internal.h"

/**
 * @brief Sends an "edi" (egg died) message to all graphical clients.
 *
 * This function formats and broadcasts a message indicating that an egg,
 * identified by its number, has died. The message is sent to all connected
 * graphical clients using the provided context.
 *
 * @param ctxt Pointer to the parsed server context used for broadcasting.
 * @param egg Pointer to the egg structure containing the egg's number.
 */
void send_edi(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg)
{
    char *block;

    block = snprintf_alloc("edi #%ld\n", egg->number);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
