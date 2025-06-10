/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** run_server
*/

#include "server_internal.h"

/**
 * @brief Checks if it's time to spawn new resources on the map and triggers
 * the spawn if needed.
 *
 * This function compares the current time with the calculated time for the
 * next resource spawn, based on the server's frequency and the last spawn
 * time. If the current time exceeds or equals the scheduled spawn time, it
 * calls generate_map() to spawn resources and updates the last spawn time.
 *
 * @param ctxt Pointer to the parsed server context containing server state and
 * map information.
 */
static void check_ressources_spawn(zap_srv_t *server, zap_srv_map_t *map)
{
    double current_time = get_time();
    double real_time = server->last_spawn +
        (ZAP_SRV_RESOURCE_SPAWN_TIMER / (double)server->frequency);

    if (current_time >= real_time) {
        generate_map(map);
        server->last_spawn = get_time();
    }
}

/**
 * @brief Initializes the server structure and prepares it to accept clients.
 *
 * This function sets up the server socket, allocates memory for the client
 * structures, and initializes the file descriptor and port lists. It also
 * resets the number of connected clients to zero.
 *
 * @param server Pointer to the zap_srv_t server structure to initialize.
 */
static void init_server(zap_srv_t *server)
{
    init_server_socket(server);
    server->clients = safe_calloc(ZAP_SRV_MAX_CLIENTS,
        sizeof(zap_srv_player_t), NULL);
    server->fds[0].fd = server->sock.fd;
    server->fds[0].events = POLLIN;
    for (int i = 1; i <= ZAP_SRV_MAX_CLIENTS; ++i) {
        server->fds[i].fd = -1;
        server->fds[i].events = POLLIN;
        server->port_list[i - 1] = -1;
        server->clients[i - 1].sock.fd = -1;
    }
    server->num_clients = 0;
    server->last_spawn = get_time();
}

/**
 * @brief Attempts to accept new client connections for the server.
 *
 * This function wraps the call to accept_new_clients() in an exception
 * handling block to catch memory allocation failures
 * (CEXTEND_EXCEPTION_BAD_ALLOC). If such an exception occurs, the function
 * returns early to prevent further  processing. Otherwise, it proceeds to
 * accept new clients as normal.
 *
 * @param ctxt Pointer to the parsed server context structure.
 */
static void try_accept_clients(zap_srv_parsed_context_t *ctxt)
{
    cextend_exception_code_t code = 0;
    cextend_exception_context_t *except_ctxt = INIT_TRY;

    TRY(code, except_ctxt) {
        accept_new_clients(ctxt);
    } CATCH(code, CEXTEND_EXCEPTION_BAD_ALLOC) {
        END_TRY;
        return;
    } CATCH_END(code);
    END_TRY;
}

/**
 * @brief Checks if the game is over by determining if only one team remains
 * active.
 *
 * Iterates through the list of teams in the given context. A team is
 * considered active if it has available slots or connected clients. If more
 * than one active team is found, the game is not over and the function returns
 * false. If only one active team remains, it sends a message to the graphical
 * clients, logs the game end, and returns true to indicate the game is over.
 *
 * @param ctxt Pointer to the parsed server context containing the list of
 * teams.
 * @return true if the game is over (only one team remains active), false
 * otherwise.
 */
static bool game_over(zap_srv_parsed_context_t *ctxt)
{
    zap_srv_team_t *winner = NULL;
    zap_srv_team_t *winner2 = NULL;

    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (tmp->max_elevation_players >= ZAP_SRV_MAX_ELEVATION_WIN) {
            winner = tmp;
            break;
        }
        if (tmp->available_slots > 0 || tmp->num_clients > 0) {
            winner2 = winner;
            winner = tmp;
        }
        if (winner && winner2) {
            return false;
        }
    }
    send_seg(ctxt, winner);
    CEXTEND_LOG(CEXTEND_LOG_INFO, "Game ended. Stopping server...");
    return true;
}

/**
 * @brief Executes a single routine cycle for the server.
 *
 * This function checks if the game is over by calling `game_over()`.
 * If the game is over, it returns false to indicate the routine should stop.
 * Otherwise, it spawns resources on the map by calling
 * `check_ressources_spawn()` and returns true to continue the routine.
 *
 * @param ctxt Pointer to the parsed server context structure.
 * @return true if the routine should continue, false if the game is over.
 */
static bool run_routine(zap_srv_parsed_context_t *ctxt)
{
    if (game_over(ctxt)) {
        return false;
    }
    check_ressources_spawn(&ctxt->server, &ctxt->map);
    return true;
}

/**
 * @brief Runs the main server loop, handling client connections and messages.
 *
 * This function initializes the server, then enters a loop that continues
 * as long as the server is instructed to keep running. Within the loop,
 * it uses poll() to monitor file descriptors for incoming connections or
 * messages. If a new client attempts to connect, it accepts the connection.
 * It also reads messages from connected clients. The loop can be interrupted
 * by external signals or poll failures, in which case the server socket is
 * properly closed before exiting.
 *
 * @param ctxt Pointer to the parsed server context structure containing
 *        server state and configuration.
 */
void run_server(zap_srv_parsed_context_t *ctxt)
{
    int poll_count = -1;

    init_server(&ctxt->server);
    while (keep_running(false) && run_routine(ctxt)) {
        poll_count = poll(ctxt->server.fds,
            (nfds_t)(ctxt->server.num_clients + 1), ZAP_SRV_TIMEOUT);
        if (keep_running(false) && poll_count < 0) {
            CEXTEND_LOG(CEXTEND_LOG_INFO, fetch_string(ZAP_SRV_POLL_FAIL));
            break;
        }
        if (keep_running(false) && poll_count > 0 &&
            (ctxt->server.fds[0].revents & POLLIN)) {
            try_accept_clients(ctxt);
        }
        if (keep_running(false)) {
            read_message_from_clients(ctxt);
        }
    }
    close_sock(&ctxt->server.sock, true);
}
