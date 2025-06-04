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

typedef struct {
    int fd;
    int port;
    char *ip;
    socklen_t addr_len;
    struct sockaddr_in addr;
} zap_srv_socket_t;

#endif /* !ZAP_SRV_SOCKET_H_ */
