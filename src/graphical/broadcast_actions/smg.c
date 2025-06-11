/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "smg" (server message) broadcast to all graphical clients.
 *
 * This function formats the given message with the "smg" prefix and broadcasts
 * it to all connected graphical clients using the provided context.
 *
 * @param ctxt Pointer to the server's parsed context structure.
 * @param msg The message string to be sent to graphical clients.
 */
void send_smg(zap_srv_parsed_context_t *ctxt, const char *msg)
{
    char *block;

    block = snprintf_alloc("smg %s\n", msg);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
