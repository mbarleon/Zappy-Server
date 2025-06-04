/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** close_socket
*/

#include "server_internal.h"

/**
 * @brief Closes the socket and frees associated resources.
 *
 * This function safely closes the file descriptor associated with the given
 * zap_srv_socket_t structure if it is open, and then frees the memory
 * allocated for the IP address string. After closing and freeing, it sets the
 * file descriptor to -1 and the IP pointer to NULL to prevent dangling
 * references.
 *
 * @param sock Pointer to the zap_srv_socket_t structure representing the
 * socket to close.
 */
void close_sock(zap_srv_socket_t *sock)
{
    if (sock->fd != -1) {
        close(sock->fd);
        sock->fd = -1;
    }
    if (sock->ip) {
        safe_free((void **)&sock->ip);
        sock->ip = NULL;
    }
}
