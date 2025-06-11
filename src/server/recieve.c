/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** recieve
*/

#include "server_internal.h"

/**
 * @brief Handles the unexpected disconnection of a client.
 *
 * This function is called when a client disconnects unexpectedly from the
 * server. It searches for the team associated with the disconnected client and
 * decrements the team's client count if found. If the team is not found, it
 * sends a player disconnect information (PDI) message and disconnects the
 * client from the server.
 *
 * @param ctxt Pointer to the parsed server context containing server and team
 * information.
 * @param i Index of the client in the server's client array.
 */
static void handle_unexpected_disconnect(zap_srv_parsed_context_t *ctxt,
    size_t i)
{
    zap_srv_player_t client = ctxt->server.clients[i];

    if (!client.team) {
        disconnect_client(&ctxt->server, i);
        return;
    }
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, client.team) == 0) {
            tmp->num_clients -= 1;
            break;
        }
    }
    send_pdi(ctxt, &client);
    disconnect_client(&ctxt->server, i);
}

/**
 * @brief Executes the appropriate action for a connected client based on their
 * team.
 *
 * This function checks the client's team and determines which set of actions
 * to perform:
 * - If the client's team is "GRAPHIC" and the 'read' condition is true, it
 *   calls graphic_actions().
 * - If the client's team is not NULL and not "GRAPHIC", it calls
 *   player_actions().
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the client/player structure.
 * @param i Index or identifier for the client.
 */
static void do_connected_action(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, size_t i, bool read)
{
    int cmp;

    cmp = strcmp(client->team, "GRAPHIC");
    if (read && cmp == 0) {
        graphic_actions(ctxt, client);
        return;
    }
    if (client->team != NULL && cmp != 0) {
        player_actions(ctxt, client, i);
        return;
    }
}

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
        handle_unexpected_disconnect(ctxt, i);
        return;
    }
    if (read && client->team == NULL) {
        connect_client(client, ctxt);
        return;
    }
    if (client->team == NULL) {
        return;
    }
    do_connected_action(ctxt, client, i, read);
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
            handle_unexpected_disconnect(ctxt, i);
        }
        if (i >= ctxt->server.num_clients) {
            break;
        }
        if (ctxt->server.fds[i + 1].revents & (POLLHUP | POLLERR)) {
            handle_client_disconnect(&ctxt->server.clients[i].sock);
            handle_unexpected_disconnect(ctxt, i);
            continue;
        }
        if (ctxt->server.fds[i + 1].revents & POLLIN) {
            try_do_action(ctxt, &ctxt->server.clients[i], i, true);
            continue;
        }
        try_do_action(ctxt, &ctxt->server.clients[i], i, false);
    }
}
