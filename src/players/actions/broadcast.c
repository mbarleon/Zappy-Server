/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** broadcast
*/

#include "actions.h"

void player_broadcast(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    (void)ctxt;
    send_client("not implemented (ko)\n", &client->sock);
}
