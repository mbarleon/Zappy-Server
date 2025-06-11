/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** send_clients
*/

#include "server_internal.h"

/**
 * @brief Sends a message to a client socket.
 *
 * This function attempts to send the specified buffer to the given client
 * socket.  It first checks for socket errors using getsockopt. If an error is
 * detected, the client is disconnected via handle_client_disconnect.
 *
 * If the buffer is NULL, a default message (fetched by
 * fetch_msg(ZAP_SRV_MSG_MAX)) is sent instead. If sending the message fails or
 * the number of bytes written is less than the message length, the client is
 * disconnected.
 *
 * @param buffer The message to send to the client. If NULL, a default message
 * is sent.
 * @param client Pointer to the zap_srv_socket_t structure representing the
 * client.
 */
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
