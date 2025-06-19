/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** broadcast
*/

#include "actions.h"

/**
 * @brief Determines the orientation index based on the given vector (dx, dy).
 *
 * This function returns an integer representing the orientation derived from
 * the direction vector (dx, dy). The mapping is as follows:
 *   0: No movement  (dx == 0 && dy == 0)
 *   1: Left         (dx < 0 && dy == 0)
 *   2: Up-Left      (dx < 0 && dy > 0)
 *   3: Up           (dx == 0 && dy > 0)
 *   4: Up-Right     (dx > 0 && dy > 0)
 *   5: Right        (dx > 0 && dy == 0)
 *   6: Down-Right   (dx > 0 && dy < 0)
 *   7: Down         (dx == 0 && dy < 0)
 *   8: Down-Left    (any other case, but thechnically the only combination
 *                    that is not tested is dx < 0 && dy < 0)
 *
 * @param dx The change in the x-direction.
 * @param dy The change in the y-direction.
 * @return int The orientation index corresponding to the vector.
 */
static int orientation_from_vector(ssize_t dx, ssize_t dy)
{
    if (dx == 0 && dy == 0)
        return 0;
    if (dx < 0 && dy == 0)
        return 1;
    if (dx < 0 && dy > 0)
        return 2;
    if (dx == 0 && dy > 0)
        return 3;
    if (dx > 0 && dy > 0)
        return 4;
    if (dx > 0 && dy == 0)
        return 5;
    if (dx > 0 && dy < 0)
        return 6;
    if (dx == 0 && dy < 0)
        return 7;
    return 8;
}

/**
 * @brief Rotates a direction index based on the listener's orientation.
 *
 * This function adjusts the given orientation relative to the listener's
 * orientation,
 * effectively rotating the direction so that it is correct from the listener's
 * perspective.
 *
 * @param orientation The original orientation (1 to 8, where 0 means no
 * orientation).
 * @param listener_orientation The orientation of the listener (1 to 4).
 * @return The rotated orientation index (1 to 8), or 0 if the original
 * orientation is 0.
 */
static int rotate_orientation(int orientation, int listener_orientation)
{
    int shift;
    int rotated_index;
    int direction_index;

    if (orientation == 0) {
        return 0;
    }
    direction_index = orientation - 1;
    shift = (listener_orientation - 1) * 2;
    rotated_index = (direction_index - shift + 8) % 8;
    return rotated_index + 1;
}

/**
 * @brief Calculates the sound orientation from a source position to a
 * destination position, taking into account map wrapping and the listener's
 * orientation.
 *
 * This function computes the direction (orientation) from the source position
 * (`src`) to the destination position (`dst`) on a toroidal (wrapping) map. It
 * adjusts the vector between the two positions to account for map wrapping,
 * determines the base orientation using `orientation_from_vector`, and then
 * rotates this orientation according to the listener's current orientation.
 *
 * @param src Pointer to the source position structure.
 * @param dst Pointer to the destination position structure.
 * @param ctxt Pointer to the parsed context structure (unused in this
 * function).
 * @param listener_orientation The orientation of the listener to adjust the
 * result.
 * @return The computed sound orientation relative to the listener.
 */
static int get_sound_orientation(zap_srv_pos_t *src, zap_srv_pos_t *dst,
    zap_srv_parsed_context_t *ctxt, int listener_orientation)
{
    int base_orientation;
    ssize_t dx = dst->x - src->x;
    ssize_t dy = dst->y - src->y;

    if (dx > ctxt->map.x / 2) {
        dx -= ctxt->map.x;
    }
    if (dx < (-1 * ctxt->map.x) / 2) {
        dx += ctxt->map.x;
    }
    if (dy > ctxt->map.y / 2) {
        dy -= ctxt->map.y;
    }
    if (dy < (-1 * ctxt->map.y) / 2) {
        dy += ctxt->map.y;
    }
    base_orientation = orientation_from_vector(dx, dy);
    return rotate_orientation(base_orientation, listener_orientation);
}

/**
 * @brief Sends a broadcast message block from one player to another.
 *
 * Constructs a formatted broadcast message indicating the direction of the
 * sound relative to the destination player, appends a newline if necessary,
 * and sends it to the destination player's socket.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player sending the broadcast.
 * @param dest Pointer to the player receiving the broadcast.
 * @param msg The message to broadcast.
 */
static void send_broadcast_block(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, zap_srv_player_t *dest, const char *msg)
{
    char *block = NULL;

    if (!msg || strlen(msg) == 0) {
        return;
    }
    block = snprintf_alloc("message %d, %s\n", get_sound_orientation(
        &client->pos, &dest->pos, ctxt, (int)dest->orientation), msg);
    if (block) {
        send_client(block, &dest->sock);
        free(block);
    }
}

/**
 * @brief Broadcasts a message from a player to all other players except those
 * in the "GRAPHIC" team and the sender.
 *
 * This function iterates through all connected clients and sends the broadcast
 * message to each client who is not part of the "GRAPHIC" team and is not the
 * sender. After broadcasting, it notifies the sender and acknowledges the
 * broadcast command.
 *
 * @param ctxt Pointer to the parsed server context containing server and
 * client information.
 * @param client Pointer to the player initiating the broadcast.
 * @param arguments The message to be broadcasted to other players.
 * @return true on successful broadcast, false otherwise.
 */
bool player_broadcast(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments)
{
    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        if (ctxt->server.clients[i].team &&
            strcmp("GRAPHIC", ctxt->server.clients[i].team) != 0 &&
            ctxt->server.clients[i].id != client->id) {
                send_broadcast_block(ctxt, client, &(ctxt->server.clients[i]),
                    arguments);
        }
    }
    send_pbc(ctxt, client, arguments);
    send_client("ok\n", &client->sock);
    return true;
}
