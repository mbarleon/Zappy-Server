/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** run_server
*/

#include "server_internal.h"

static void init_server(zap_srv_t *server)
{
    init_server_socket(server);
}

void run_server(zap_srv_parsed_context_t *ctxt)
{
    init_server(&ctxt->server);
    while (keep_running(false)) {
        continue;
    }
    close_sock(&ctxt->server.sock);
}
