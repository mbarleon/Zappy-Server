/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** graphical_broadcast
*/

#include "graphical_internal.h"

/**
 * @brief Sends a broadcast message to all connected graphical clients.
 *
 * Iterates through the list of server clients and sends the specified message
 * to each client whose team is "GRAPHIC". The message is sent using the
 * send_client function.
 *
 * @param ctxt Pointer to the parsed server context containing client
 * information.
 * @param str The message string to broadcast to graphical clients.
 */
void graphical_broadcast(zap_srv_parsed_context_t *ctxt, const char *str)
{
    for (size_t i = 0; i < ZAP_SRV_MAX_CLIENTS; ++i) {
        if (ctxt->server.clients[i].team &&
            strcmp(ctxt->server.clients[i].team, "GRAPHIC") == 0) {
            send_client(str, &ctxt->server.clients[i].sock);
        }
    }
}
