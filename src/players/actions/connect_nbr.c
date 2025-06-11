/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** connect_nbr
*/

#include "actions.h"

/**
 * @brief Returns the minimum of two size_t values.
 *
 * Compares the two input values and returns the smaller one.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @return The smaller of the two input values.
 */
static size_t my_min(size_t a, size_t b)
{
    return a < b ? a : b;
}

/**
 * @brief Sends the number of available connection slots for a team to a
 * client.
 *
 * This function formats the number of available slots in the given team as a
 * string, sends it to the specified client, and frees the allocated memory.
 *
 * @param client Pointer to the client structure to which the information will
 * be sent.
 * @param team Pointer to the team structure containing the available slots
 * information.
 */
static void send_connct_nbr(zap_srv_player_t *client, zap_srv_team_t *team)
{
    char *block;

    block = snprintf_alloc("%ld\n", my_min(team->available_slots,
        team->max_clients - team->num_clients));
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}

/**
 * @brief Handles the "connect_nbr" action for a player.
 *
 * This function searches for the team associated with the given player
 * in the parsed server context. If the team is found, it sends the
 * "connect_nbr" response to the player, indicating the number of available
 * connection slots for that team.
 *
 * @param ctxt Pointer to the parsed server context containing team
 * information.
 * @param client Pointer to the player requesting the "connect_nbr" action.
 * @param arguments Arguments for the function (unused).
 */
bool player_connect_nbr(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, UNUSED const char *arguments)
{
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, client->team) == 0) {
            send_connct_nbr(client, tmp);
            return true;
        }
    }
    send_client("ko\n", &client->sock);
    return false;
}
