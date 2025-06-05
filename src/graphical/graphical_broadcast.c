/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** graphical_broadcast
*/

#include "graphical_internal.h"

void graphical_broadcast(zap_srv_parsed_context_t *ctxt, const char *str)
{
    for (size_t i = 0; i < ZAP_SRV_MAX_CLIENTS; ++i) {
        if (ctxt->server.clients[i].team &&
            strcmp(ctxt->server.clients[i].team, "GRAPHIC") == 0) {
            send_client(str, &ctxt->server.clients[i].sock);
        }
    }
}
