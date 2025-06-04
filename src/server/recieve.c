/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** recieve
*/

#include "server_internal.h"

static void do_action(UNUSED zap_srv_parsed_context_t *ctxt, UNUSED size_t i)
{
    return;
}

void read_message_from_clients(zap_srv_parsed_context_t *ctxt)
{
    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        while (ctxt->server.clients[i].sock.fd == ZAP_SRV_SOCK_ERROR) {
            disconnect_client(&ctxt->server, i);
        }
        if (ctxt->server.fds[i + 1].revents & (POLLHUP | POLLERR)) {
            handle_client_disconnect(&ctxt->server.clients[i].sock);
            disconnect_client(&ctxt->server, i);
            continue;
        }
        if (ctxt->server.fds[i + 1].revents & POLLIN)
            do_action(ctxt, i);
    }
}
