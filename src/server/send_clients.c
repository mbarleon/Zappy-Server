/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** send_clients
*/

#include "server_internal.h"

void send_client(const char *buffer, zap_srv_socket_t *client)
{
    int ret;
    int error = 0;
    socklen_t len = sizeof(error);

    if (getsockopt(client->fd, SOL_SOCKET, SO_ERROR, &error, &len) != 0) {
        handle_client_disconnect(client);
        return;
    }
    if (!buffer) {
        ret = dprintf(client->fd, fetch_msg(ZAP_SRV_MSG_MAX));
        if (ret == -1 || (size_t)ret < strlen(fetch_msg(ZAP_SRV_MSG_MAX))) {
            handle_client_disconnect(client);
            return;
        }
    }
    ret = dprintf(client->fd, buffer);
    if (ret == -1 || (size_t)ret < strlen(buffer)) {
        handle_client_disconnect(client);
        return;
    }
}
