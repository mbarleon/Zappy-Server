/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** right
*/

#include "actions.h"

/**
 * @brief Rotates the player's orientation 90 degrees to the right.
 *
 * This function updates the orientation of the given player (`client`) by
 * turning them to the right (clockwise). The orientation cycles through
 * NORTH -> EAST -> SOUTH -> WEST -> NORTH. After updating the orientation, it
 * sends an "ok" response to the client.
 *
 * @param ctxt Parsed context parameter.
 * @param client Pointer to the player whose orientation will be updated.
 * @param arguments Unused arguments for the function.
 */
void player_right(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED const char *arguments)
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
    send_ppo(ctxt, client);
}
