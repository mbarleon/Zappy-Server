/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** accept_clients
*/

#include "server_internal.h"

static int accept_client(int serverfd, zap_srv_socket_t *client_sock)
{
    client_sock->fd = accept(serverfd, (struct sockaddr*)&client_sock->addr,
        &client_sock->addr_len);
    if (client_sock->fd == -1) {
        CEXTEND_LOG(CEXTEND_LOG_WARNING, fetch_string(ZAP_SRV_ACCEPT_FAIL));
        return ZAP_SRV_ERROR;
    }
    inet_ntop(AF_INET, &client_sock->addr.sin_addr, client_sock->ip,
        INET_ADDRSTRLEN);
    client_sock->port = ntohs(client_sock->addr.sin_port);
    return ZAP_SRV_SUCCESS;
}

static void init_client(zap_srv_socket_t *client_sock)
{
    client_sock->fd = -1;
    client_sock->port = -1;
    client_sock->ip = safe_calloc(INET_ADDRSTRLEN + 1, sizeof(char), NULL);
    client_sock->addr_len = sizeof(client_sock->addr);
    memset(&(client_sock->addr), 0, client_sock->addr_len);
}

void accept_new_clients(UNUSED zap_srv_parsed_context_t *ctxt)
{
    zap_srv_player_t client = ctxt->server.clients[ctxt->server.num_clients];

    if (ctxt->server.num_clients >= ZAP_SRV_MAX_CLIENTS) {
        CEXTEND_LOG(CEXTEND_LOG_WARNING, fetch_string(ZAP_SRV_MAX_CLIENT_ERR));
        return;
    }
    init_client(&client.sock);
    if (accept_client(ctxt->server.sock.fd, &client.sock) == ZAP_SRV_ERROR) {
        safe_free((void **)&client.sock.ip);
        return;
    }
    CEXTEND_LOG(CEXTEND_LOG_INFO, fetch_string(ZAP_SRV_CLIENT_CONNECT),
        ctxt->server.num_clients, client.sock.ip, client.sock.port);
    ctxt->server.num_clients += 1;
    ctxt->server.fds[ctxt->server.num_clients].fd = client.sock.fd;
    ctxt->server.fds[ctxt->server.num_clients].events = POLLIN;
    send_client(fetch_msg(ZAP_SRV_WELCOME), &client.sock);
}
