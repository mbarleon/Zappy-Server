/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** server_internal
*/

#ifndef ZAP_SRV_SERVER_INTERNAL_H_
    #define ZAP_SRV_SERVER_INTERNAL_H_
    #include "macro.h"
    #include "server.h"
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <signal.h>
    #include <stdbool.h>
    #include <arpa/inet.h>
    #include <cextend/macro.h>
    #include <cextend/logger.h>
    #include <cextend/memory.h>
    #include "zap_srv_socket.h"
    #include <cextend/exception.h>

    #define ZAP_SRV_MAX_SIGINT 3
    #define ZAP_SRV_MAX_CLIENTS 100000

bool keep_running(bool running);
void handle_signals(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext);
void close_sock(zap_srv_socket_t *sock);
void init_server_socket(zap_srv_t *srv);

#endif /* !ZAP_SRV_SERVER_INTERNAL_H_ */
