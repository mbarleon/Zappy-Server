/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** recieve
*/

#include "server_internal.h"

/**
 * @brief Handles actions for a specific client in the server context.
 *
 * This function processes incoming data from a client, manages their
 * connection status, and dispatches actions based on the client's team
 * affiliation.
 * - If receiving data fails, the client is disconnected.
 * - If the client is not yet associated with a team, attempts to connect them.
 * - If the client is part of the "GRAPHIC" team, executes graphic-specific
 *   actions.
 * - Otherwise, executes standard player actions.
 *
 * @param ctxt   Pointer to the parsed server context.
 * @param client Pointer to the client/player structure.
 * @param i      Index of the client in the server's client list.
 * @param read   Boolean that tells the server wether it should read from the
 * client.
 */
static void do_action(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    size_t i, bool read)
{
    if (read &&
        recv_client(&client->buf, &client->sock, &client->buf_size) == -1) {
        disconnect_client(&ctxt->server, i);
        return;
    }
    if (read && client->team == NULL) {
        connect_client(client, ctxt);
        return;
    }
    if (read && strcmp(client->team, "GRAPHIC") == 0) {
        graphic_actions(client);
        return;
    }
    if (client->team != NULL) {
        player_actions(ctxt, client);
        return;
    }
}

/**
 * @brief Attempts to perform an action for a given client,
 * handling exceptions.
 *
 * This function wraps the call to `do_action()` in a try-catch block to handle
 * specific exceptions that may occur during the action execution for a client.
 * If an exception is caught (such as bad allocation, invalid argument, or
 * length error), it logs the error and disconnects the client from the server.
 *
 * @param ctxt   Pointer to the parsed server context.
 * @param client Pointer to the client/player structure.
 * @param i      Index of the client in the server's client list.
 */
static void try_do_action(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, size_t i, bool read)
{
    cextend_exception_code_t code = 0;
    cextend_exception_context_t *except_ctxt = INIT_TRY;

    TRY(code, except_ctxt) {
        do_action(ctxt, client, i, read);
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

/**
 * @brief Reads and processes messages from all connected clients.
 *
 * Iterates through the list of connected clients, handling disconnections and
 * incoming messages.
 * - If a client's socket is in an error state (ZAP_SRV_SOCK_ERROR), the client
 *   is disconnected.
 * - If a client's file descriptor signals a hang-up or error
 *   (POLLHUP | POLLERR), the client is disconnected.
 * - If a client's file descriptor signals incoming data (POLLIN), attempts to
 *   process the client's action.
 *
 * @param ctxt Pointer to the parsed server context containing client and
 * server information.
 */
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
        if (ctxt->server.fds[i + 1].revents & POLLIN) {
            try_do_action(ctxt, &ctxt->server.clients[i], i, true);
            continue;
        }
        try_do_action(ctxt, &ctxt->server.clients[i], i, false);
    }
}
