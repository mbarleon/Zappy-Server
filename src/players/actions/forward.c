/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** forward
*/

#include "actions.h"

/**
 * @brief Moves the player one tile forward in the direction they are facing.
 *
 * This function calculates the next position of the player based on their
 * current orientation and updates their position accordingly. The movement
 * wraps around the map if the player reaches the edge. After moving, it sends
 * an "ok" message to the player's socket to acknowledge the action.
 *
 * @param ctxt Pointer to the parsed server context containing map information.
 * @param client Pointer to the player structure to be moved.
 */
void player_forward(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    zap_srv_pos_t map_size = (zap_srv_pos_t){ctxt->map.x, ctxt->map.y};
    zap_srv_pos_t new_pos =
        compute_next_position(&client->pos, client->orientation, &map_size);

    client->pos.x = new_pos.x;
    client->pos.y = new_pos.y;
    send_client("ok\n", &client->sock);
}
