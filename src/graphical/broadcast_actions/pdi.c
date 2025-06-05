/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

void send_pdi(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("pdi #%ld\n", client->id);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
