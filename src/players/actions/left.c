/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** left
*/

#include "actions.h"

/**
 * @brief Rotates the player's orientation to the left (counter-clockwise).
 *
 * This function updates the orientation of the given player to the direction
 * to their left, based on their current orientation (NORTH -> WEST, EAST ->
 * NORTH, SOUTH -> EAST, WEST -> SOUTH). After updating the orientation,
 * it sends an acknowledgment ("ok\n") to the player's socket.
 *
 * @param ctxt Unused parsed context pointer.
 * @param client Pointer to the player whose orientation will be updated.
 * @param arguments Unused arguments for the function.
 */
void player_left(UNUSED zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, UNUSED const char *arguments)
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
