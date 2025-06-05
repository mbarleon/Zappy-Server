/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pnw
*/

#include "../graphical_internal.h"

void send_pnw(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("pnw #%ld %ld %ld %d %ld %s\n", client->id,
        client->pos.x, client->pos.y, client->orientation, client->level,
        client->team);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
