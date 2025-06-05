/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** server_internal
*/

#ifndef ZAP_SRV_SERVER_INTERNAL_H_
    #define ZAP_SRV_SERVER_INTERNAL_H_
    #include <stdio.h>
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
    #include <cextend/snprintf_alloc.h>
    #include "../graphical/graphical.h"
    #include "../string/string_entry_table.h"
    #include "../string/message_entry_table.h"

    #define ZAP_SRV_MAX_SIGINT 3
    #define ZAP_SRV_TIMEOUT 10000
    #define ZAP_SRV_COMMAND_LENGTH 2048
    #define ZAP_SRV_MAX_LINE_SIZE 2097152

bool keep_running(bool running);
void handle_signals(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext);

void init_server_socket(zap_srv_t *srv);
void close_sock(zap_srv_socket_t *sock, bool is_server);

void accept_new_clients(zap_srv_parsed_context_t *ctxt);
void read_message_from_clients(zap_srv_parsed_context_t *ctxt);

ssize_t recv_client(char **line, zap_srv_socket_t *client, size_t *buf_size);
void send_client(const char *buffer, zap_srv_socket_t *client);

void disconnect_client(zap_srv_t *server, size_t i);
void handle_client_disconnect(zap_srv_socket_t *client);

void connect_client(zap_srv_player_t *client, zap_srv_parsed_context_t *ctxt);

#endif /* !ZAP_SRV_SERVER_INTERNAL_H_ */
