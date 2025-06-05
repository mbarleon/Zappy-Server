/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** inventory
*/

#include "actions.h"

void player_inventory(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    (void)ctxt;
    send_client("not implemented (ko)\n", &client->sock);
}
