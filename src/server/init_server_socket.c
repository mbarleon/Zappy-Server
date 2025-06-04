/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** init_server_socket
*/

#include "server_internal.h"


static int create_socket(zap_srv_socket_t *sock)
{
    sock->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock->fd == -1) {
        return -1;
    }
    return 0;
}

static int init_sockaddr(zap_srv_socket_t *sock, uint16_t port)
{
    sock->addr_len = sizeof(sock->addr);
    memset(&(sock->addr), 0, sock->addr_len);
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->addr.sin_port = htons(port);
    if (bind(sock->fd, (struct sockaddr *)&(sock->addr),
        sock->addr_len) == -1) {
        return ZAP_SRV_ERROR;
    }
    return 0;
}

static int init_ip(zap_srv_socket_t *sock)
{
    if (getsockname(sock->fd, (struct sockaddr *)&sock->addr,
        &sock->addr_len) == -1) {
        return ZAP_SRV_ERROR;
    }
    inet_ntop(AF_INET, &sock->addr.sin_addr, sock->ip, INET_ADDRSTRLEN);
    sock->port = ntohs(sock->addr.sin_port);
    return 0;
}

void init_server_socket(zap_srv_t *srv)
{
    srv->sock.fd = -1;
    srv->sock.ip = safe_calloc(INET_ADDRSTRLEN + 1, sizeof(char), NULL);
    if (create_socket(&srv->sock) == -1) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "socket failed.");
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    if (init_sockaddr(&srv->sock, srv->port) == ZAP_SRV_ERROR) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "bind failed.");
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    if (init_ip(&srv->sock) == ZAP_SRV_ERROR) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "getsockname failed.");
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    if (listen(srv->sock.fd, ZAP_SRV_MAX_CLIENTS) != 0) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "listen failed.");
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    CEXTEND_LOG(CEXTEND_LOG_INFO, "Server listening on %s:%d.", srv->sock.ip,
        srv->sock.port);
}
