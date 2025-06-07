/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** forward
*/

#include "actions.h"

void player_forward(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    zap_srv_pos_t map_size = (zap_srv_pos_t){ctxt->map.x, ctxt->map.y};
    zap_srv_pos_t new_pos =
        compute_next_position(&client->pos, client->orientation, &map_size);

    client->pos.x = new_pos.x;
    client->pos.y = new_pos.y;
    send_client("ok\n", &client->sock);
}
