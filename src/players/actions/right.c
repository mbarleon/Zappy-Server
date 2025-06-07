/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** right
*/

#include "actions.h"

void player_right(__attribute__((unused))zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    switch (client->orientation) {
        case NORTH:
            client->orientation = EAST;
            break;
        case EAST:
            client->orientation = SOUTH;
            break;
        case SOUTH:
            client->orientation = WEST;
            break;
        case WEST:
            client->orientation = NORTH;
            break;
        default:
            break;
    }
    send_client("ok\n", &client->sock);
}
