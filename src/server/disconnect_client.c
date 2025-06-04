/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** disconnect_client
*/

#include "server_internal.h"

void handle_client_disconnect(zap_srv_socket_t *client)
{
    CEXTEND_LOG(CEXTEND_LOG_WARNING, fetch_string(ZAP_SRV_CLIENT_ERR),
        client->fd);
    client->fd = ZAP_SRV_SOCK_ERROR;
}

void disconnect_client(zap_srv_t *server, size_t i)
{
    close_sock(&server->clients[i].sock);
    for (; i < server->num_clients - 1; ++i) {
        server->port_list[i] = server->port_list[i + 1];
        server->clients[i] = server->clients[i + 1];
        server->fds[i + 1] = server->fds[i + 2];
    }
    if (i >= ZAP_SRV_MAX_CLIENTS) {
        return;
    }
    server->port_list[i] = -1;
    server->fds[i + 1].fd = -1;
    server->fds[i + 1].events = POLLIN;
    server->num_clients -= 1;
}
