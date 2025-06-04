/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** zap_srv_socket
*/

#ifndef ZAP_SRV_SOCKET_H_
    #define ZAP_SRV_SOCKET_H_
    #include <sys/socket.h>
    #include <netinet/in.h>

/**
 * @struct zap_srv_socket_t
 * @brief Structure representing a server socket.
 *
 * This structure encapsulates all necessary information for a server socket,
 * including its file descriptor, port, IP address, address length, and socket
 * address.
 */
typedef struct {
    /**
     * @brief File descriptor for the socket.
     */
    int fd;
    /**
     * @brief Port number on which the server socket is bound.
     */
    uint16_t port;
    /**
     * @brief String representation of the IP address the socket is bound to.
     */
    char *ip;
    /**
     * @brief Length of the socket address structure.
     */
    socklen_t addr_len;
    /**
     * @brief sockaddr_in structure containing the socket address information.
     */
    struct sockaddr_in addr;
} zap_srv_socket_t;

#endif /* !ZAP_SRV_SOCKET_H_ */
