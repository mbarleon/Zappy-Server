/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** set
*/

#include "actions.h"

void player_set(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED const char *arguments)
{
    (void)ctxt;
    (void)arguments;
    send_client("not implemented (ko)\n", &client->sock);
}
