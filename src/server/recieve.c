/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** recieve
*/

#include "server_internal.h"

static void do_action(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    size_t i)
{
    if (recv_client(&client->buf, &client->sock, &client->buf_size) == -1) {
        disconnect_client(&ctxt->server, i);
        return;
    }
}

void read_message_from_clients(zap_srv_parsed_context_t *ctxt)
{
    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        while (ctxt->server.clients[i].sock.fd == ZAP_SRV_SOCK_ERROR) {
            disconnect_client(&ctxt->server, i);
        }
        if (i >= ctxt->server.num_clients) {
            break;
        }
        if (ctxt->server.fds[i + 1].revents & (POLLHUP | POLLERR)) {
            handle_client_disconnect(&ctxt->server.clients[i].sock);
            disconnect_client(&ctxt->server, i);
            continue;
        }
        if (ctxt->server.fds[i + 1].revents & POLLIN)
            do_action(ctxt, &ctxt->server.clients[i], i);
    }
}
