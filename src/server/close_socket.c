/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** close_socket
*/

#include "server_internal.h"

void close_sock(zap_srv_socket_t *sock)
{
    if (sock->fd != -1) {
        close(sock->fd);
        sock->fd = -1;
    }
    if (sock->ip) {
        free(sock->ip);
        sock->ip = NULL;
    }
}
