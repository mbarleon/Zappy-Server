/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the names of all teams to the specified graphical client.
 *
 * This function iterates through the list of teams in the server context and,
 * for each team, formats a message containing the team's name. The message is
 * then sent to the specified graphical client socket. The message format is:
 * "tna <team_name>\n".
 *
 * @param ctxt   Pointer to the server context containing the list of teams.
 * @param client Pointer to the graphical client to which the team names will
 * be sent.
 * @param args   Unused parameter (graphical arguments).
 */
void graph_tna(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED zap_srv_graph_args_t *args)
{
    char *block;

    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        block = snprintf_alloc("tna %s\n", tmp->name);
        if (block) {
            send_client(block, &client->sock);
            free(block);
        }
    }
}
