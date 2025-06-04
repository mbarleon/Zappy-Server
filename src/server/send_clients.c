/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** send_clients
*/

#include "server_internal.h"

static void print_client_disconnect(zap_srv_socket_t *client)
{
    CEXTEND_LOG(CEXTEND_LOG_WARNING, fetch_string(ZAP_SRV_CLIENT_ERR),
        client->fd);
    client->fd = -1;
}

void send_client(const char *buffer, zap_srv_socket_t *client)
{
    int ret;
    int error = 0;
    socklen_t len = sizeof(error);

    if (getsockopt(client->fd, SOL_SOCKET, SO_ERROR, &error, &len) != 0) {
        print_client_disconnect(client);
    }
    if (!buffer) {
        ret = dprintf(client->fd, fetch_msg(ZAP_SRV_MSG_MAX));
        if (ret == -1 || (size_t)ret < strlen(fetch_msg(ZAP_SRV_MSG_MAX))) {
            print_client_disconnect(client);
        }
    }
    ret = dprintf(client->fd, buffer);
    if (ret == -1 || (size_t)ret < strlen(buffer)) {
        print_client_disconnect(client);
    }
}
