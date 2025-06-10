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
    #include <sys/types.h>
    #include <arpa/inet.h>
    #include <cextend/macro.h>
    #include <cextend/logger.h>
    #include <cextend/memory.h>
    #include "../utils/utils.h"
    #include "zap_srv_socket.h"
    #include <cextend/exception.h>
    #include "../egg/egg_functions.h"
    #include <cextend/snprintf_alloc.h>
    #include "../graphical/graphical.h"
    #include "../players/player_functions.h"
    #include "../string/string_entry_table.h"
    #include "../string/message_entry_table.h"

    #define ZAP_SRV_MAX_SIGINT 3
    #define ZAP_SRV_TIMEOUT 100
    #define ZAP_SRV_MAX_ELEVATION_WIN 6
    #define ZAP_SRV_COMMAND_LENGTH 2048
    #define ZAP_SRV_MAX_LINE_SIZE 2097152
    #define ZAP_SRV_RESOURCE_SPAWN_TIMER 20.0

bool keep_running(bool running);
void handle_signals(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext);

void init_server_socket(zap_srv_t *srv);
void close_sock(zap_srv_socket_t *sock, bool is_server);

void accept_new_clients(zap_srv_parsed_context_t *ctxt);
void read_message_from_clients(zap_srv_parsed_context_t *ctxt);

ssize_t recv_client(char **line, zap_srv_socket_t *client, size_t *buf_size);

void handle_client_disconnect(zap_srv_socket_t *client);

void connect_client(zap_srv_player_t *client, zap_srv_parsed_context_t *ctxt);
void send_graphic_connect_message(zap_srv_player_t *client,
    zap_srv_parsed_context_t *ctxt);

#endif /* !ZAP_SRV_SERVER_INTERNAL_H_ */
