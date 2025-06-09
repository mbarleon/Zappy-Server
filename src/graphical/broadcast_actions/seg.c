/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** seg
*/

#include "../graphical_internal.h"

void send_seg(zap_srv_parsed_context_t *ctxt, zap_srv_team_t *team)
{
    char *block;

    if (team->seg) {
        return;
    }
    block = snprintf_alloc("seg %s\n", team->name);
    team->seg = true;
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
