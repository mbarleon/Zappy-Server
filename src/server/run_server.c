/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** run_server
*/

#include "server_internal.h"

static void init_server(zap_srv_t *server)
{
    init_server_socket(server);
    for (size_t i = 0; i < ZAP_SRV_MAX_CLIENTS; ++i) {
        server->clients.clients[i] = NULL;
        server->clients.types[i] = ZAP_SRV_NONE_CLIENT;
    }
    server->fds[0].fd = server->sock.fd;
    server->fds[0].events = POLLIN;
    for (int i = 1; i <= ZAP_SRV_MAX_CLIENTS; ++i) {
        server->fds[i].fd = -1;
        server->fds[i].events = POLLIN;
        server->port_list[i - 1] = -1;
    }
    server->num_clients = 0;
}

void run_server(zap_srv_parsed_context_t *ctxt)
{
    int poll_count = -1;

    init_server(&ctxt->server);
    while (keep_running(false)) {
        poll_count = poll(ctxt->server.fds, ctxt->server.num_clients + 1,
            ZAP_SRV_TIMEOUT);
        if (keep_running(false) && poll_count < 0) {
            CEXTEND_LOG(CEXTEND_LOG_INFO, fetch_string(ZAP_SRV_POLL_FAIL));
            break;
        }
        if (keep_running(false) && poll_count > 0 &&
            (ctxt->server.fds[0].revents & POLLIN)) {
            accept_new_clients(ctxt);
        }
        if (keep_running(false)) {
            read_message_from_clients(ctxt);
        }
    }
    close_sock(&ctxt->server.sock);
}
