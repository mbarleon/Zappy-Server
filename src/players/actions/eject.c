/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** eject
*/

#include "actions.h"

bool player_eject(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments)
{
    (void)ctxt;
    (void)arguments;
    send_client("not implemented (ko)\n", &client->sock);
    return false;
}
