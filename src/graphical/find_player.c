/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** find_player
*/

#include "actions/actions.h"

/**
 * @brief Finds the index of a player in the server's client list, excluding
 * the "GRAPHIC" team and a specific player ID.
 *
 * Iterates through the list of clients in the server context and returns the
 * index of the first client whose team is not "GRAPHIC" and whose ID matches
 * the given ID. If no such client is found, sends an error message ("sbp\n")
 * to the specified client and returns SIZE_MAX.
 *
 * @param ctxt Pointer to the server context containing the list of clients.
 * @param client Pointer to the client structure to which an error message may
 * be sent.
 * @param id The player ID to exclude from the search.
 * @return The index of the matching player in the client list, or SIZE_MAX if
 * not found.
 */
size_t find_player_index(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, ssize_t id)
{
    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        if (ctxt->server.clients[i].team &&
            strcmp("GRAPHIC", ctxt->server.clients[i].team) != 0 &&
            ctxt->server.clients[i].id == id) {
            return i;
        }
    }
    send_client("sbp\n", &client->sock);
    return SIZE_MAX;
}
