/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** left
*/

#include "actions.h"

void player_left(__attribute__((unused))zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    switch (client->orientation) {
        case NORTH:
            client->orientation = WEST;
            break;
        case EAST:
            client->orientation = NORTH;
            break;
        case SOUTH:
            client->orientation = EAST;
            break;
        case WEST:
            client->orientation = SOUTH;
            break;
        default:
            break;
    }
    send_client("ok\n", &client->sock);
}
