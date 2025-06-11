/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** disconnect_client
*/

#include "server_internal.h"

/**
 * @brief Handles the disconnection process for a client socket.
 *
 * Logs a warning message indicating a client error, closes the socket if it
 * is valid, and marks the client's file descriptor as an error state.
 *
 * @param client Pointer to the zap_srv_socket_t structure representing the
 * client to disconnect.
 */
void handle_client_disconnect(zap_srv_socket_t *client)
{
    if (client->fd <= STDERR_FILENO) {
        return;
    }
    CEXTEND_LOG(CEXTEND_LOG_WARNING, fetch_string(ZAP_SRV_CLIENT_ERR),
        client->fd);
    close_sock(client, false);
    client->fd = ZAP_SRV_SOCK_ERROR;
}

/**
 * @brief Disconnects a client from the server and cleans up associated
 * resources.
 *
 * This function safely disconnects the client at the specified index `i` from
 * the server.
 * It performs the following actions:
 * - Frees the memory allocated for the client's team name.
 * - Closes the client's socket.
 * - Shifts the remaining clients, port list, and file descriptors to fill the
 *   gap.
 * - Resets the last client slot and associated resources.
 * - Decrements the total number of connected clients.
 *
 * @param server Pointer to the server structure containing client information.
 * @param i Index of the client to disconnect in the server's client array.
 */
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
