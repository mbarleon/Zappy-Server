/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** recieve
*/

#include "server_internal.h"

static void do_action(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    size_t i)
{
    if (recv_client(&client->buf, &client->sock, &client->buf_size) == -1) {
        disconnect_client(&ctxt->server, i);
        return;
    }
    if (client->team == NULL) {
        connect_client(client, ctxt);
    } else if (strcmp(client->team, "GRAPHIC") == 0) {
        graphic_actions(client);
    } else {
        player_actions(client);
    }
}

static void try_do_action(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, size_t i)
{
    cextend_exception_code_t code = 0;
    cextend_exception_context_t *except_ctxt = INIT_TRY;

    TRY(code, except_ctxt) {
        do_action(ctxt, client, i);
    } CATCH(code, CEXTEND_EXCEPTION_BAD_ALLOC) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_CAUGHT_ERROR),
            "client handling", get_exception_str(code));
        disconnect_client(&ctxt->server, i);
    } CATCH(code, CEXTEND_EXCEPTION_INVALID_ARGUMENT) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_CAUGHT_ERROR),
            "client handling", get_exception_str(code));
        disconnect_client(&ctxt->server, i);
    } CATCH(code, CEXTEND_EXCEPTION_LENGTH_ERROR) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_CAUGHT_ERROR),
            "client handling", get_exception_str(code));
        disconnect_client(&ctxt->server, i);
    } CATCH_END(code);
    END_TRY;
}

void read_message_from_clients(zap_srv_parsed_context_t *ctxt)
{
    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        while (ctxt->server.clients[i].sock.fd == ZAP_SRV_SOCK_ERROR) {
            disconnect_client(&ctxt->server, i);
        }
        if (i >= ctxt->server.num_clients) {
            break;
        }
        if (ctxt->server.fds[i + 1].revents & (POLLHUP | POLLERR)) {
            handle_client_disconnect(&ctxt->server.clients[i].sock);
            disconnect_client(&ctxt->server, i);
            continue;
        }
        if (ctxt->server.fds[i + 1].revents & POLLIN)
            try_do_action(ctxt, &ctxt->server.clients[i], i);
    }
}
