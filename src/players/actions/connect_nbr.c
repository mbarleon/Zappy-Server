/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** connect_nbr
*/

#include "actions.h"

static void send_connct_nbr(zap_srv_player_t *client, zap_srv_team_t *team)
{
    char *block;

    block = snprintf_alloc("%ld\n", team->available_slots);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}

void player_connect_nbr(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, client->team) == 0) {
            send_connct_nbr(client, tmp);
            return;
        }
    }
}
