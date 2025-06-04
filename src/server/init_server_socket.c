/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** init_server_socket
*/

#include "server_internal.h"


/**
 * @brief Creates a TCP socket and assigns its file descriptor to the given
 * zap_srv_socket_t structure.
 *
 * This function initializes a socket using the IPv4 address family (AF_INET),
 * stream socket type (SOCK_STREAM), and TCP protocol (IPPROTO_TCP).
 * The resulting file descriptor is stored in the provided zap_srv_socket_t
 * structure.
 *
 * @param sock Pointer to a zap_srv_socket_t structure where the socket file
 * descriptor will be stored.
 * @return ZAP_SRV_SUCCESS on success, or ZAP_SRV_ERROR on failure.
 */
static int create_socket(zap_srv_socket_t *sock)
{
    sock->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock->fd == -1) {
        return ZAP_SRV_ERROR;
    }
    return ZAP_SRV_SUCCESS;
}

/**
 * @brief Initializes the sockaddr_in structure for a server socket and binds
 * it to the specified port.
 *
 * This function sets up the address family, IP address (INADDR_ANY), and port
 * for the given zap_srv_socket_t structure. It then attempts to bind the
 * socket file descriptor to the specified address and port.
 *
 * @param sock Pointer to a zap_srv_socket_t structure representing the server
 * socket.
 * @param port The port number to bind the socket to (in host byte order).
 * @return ZAP_SRV_SUCCESS on success, ZAP_SRV_ERROR on failure
 * (e.g., if bind fails).
 */
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
    return ZAP_SRV_SUCCESS;
}

/**
 * @brief Initializes the IP address and port information for a server socket.
 *
 * This function retrieves the local address information of the given socket
 * file descriptor using getsockname, converts the IP address to a
 * human-readable string using inet_ntop, and stores the port number in host
 * byte order.
 *
 * @param sock Pointer to a zap_srv_socket_t structure representing the server
 * socket.
 * @return ZAP_SRV_SUCCESS on success, ZAP_SRV_ERROR on failure.
 */
static int init_ip(zap_srv_socket_t *sock)
{
    if (getsockname(sock->fd, (struct sockaddr *)&sock->addr,
        &sock->addr_len) == -1) {
        return ZAP_SRV_ERROR;
    }
    inet_ntop(AF_INET, &sock->addr.sin_addr, sock->ip, INET_ADDRSTRLEN);
    sock->port = ntohs(sock->addr.sin_port);
    return ZAP_SRV_SUCCESS;
}

/**
 * @brief Initializes the server socket for the Zappy server.
 *
 * This function sets up the server socket by allocating memory for the IP
 * address, creating the socket, initializing the socket address structure,
 * retrieving the socket's IP address, and setting the socket to listen for
 * incoming connections. If any step fails, an error is logged and a runtime
 * exception is thrown.
 *
 * @param srv Pointer to the zap_srv_t structure representing the server
 * context.
 *
 * @throws CEXTEND_EXCEPTION_RUNTIME_ERROR if socket creation, binding,
 * IP retrieval, or listening fails.
 */
void init_server_socket(zap_srv_t *srv)
{
    srv->sock.fd = -1;
    srv->sock.ip = safe_calloc(INET_ADDRSTRLEN + 1, sizeof(char), NULL);
    if (create_socket(&srv->sock) == ZAP_SRV_ERROR) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_SOCKET_FAIL));
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    if (init_sockaddr(&srv->sock, srv->port) == ZAP_SRV_ERROR) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_BIND_FAIL));
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    if (init_ip(&srv->sock) == ZAP_SRV_ERROR) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_GETSOCKNAME_FAIL));
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    if (listen(srv->sock.fd, ZAP_SRV_MAX_CLIENTS) != 0) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_LISTEN_FAIL));
        THROW(CEXTEND_EXCEPTION_RUNTIME_ERROR);
    }
    CEXTEND_LOG(CEXTEND_LOG_INFO, fetch_string(ZAP_SRV_SERVER_START),
        srv->sock.ip, srv->sock.port);
}
