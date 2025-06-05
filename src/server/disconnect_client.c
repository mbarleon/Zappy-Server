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
    if (client->fd > STDERR_FILENO) {
        close_sock(client, false);
    }
    client->fd = ZAP_SRV_SOCK_ERROR;
}

void disconnect_client(zap_srv_t *server, size_t i)
{
    char *team = server->clients[i].team;

    if (server->num_clients <= 0)
        return;
    safe_free((void **)&team);
    close_sock(&server->clients[i].sock, false);
    for (; i < server->num_clients - 1; ++i) {
        server->port_list[i] = server->port_list[i + 1];
        server->clients[i] = server->clients[i + 1];
        server->fds[i + 1] = server->fds[i + 2];
    }
    if (i >= ZAP_SRV_MAX_CLIENTS)
        return;
    server->port_list[server->num_clients - 1] = -1;
    memset(&server->clients[server->num_clients - 1], 0,
        sizeof(zap_srv_player_t));
    server->clients[server->num_clients - 1].sock.fd = ZAP_SRV_SOCK_ERROR;
    server->fds[server->num_clients].fd = -1;
    server->fds[server->num_clients].events = POLLIN;
    server->num_clients -= 1;
}
