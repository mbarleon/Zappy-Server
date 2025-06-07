/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** compute_position
*/

#include "map_internal.h"

/**
 * @brief Computes the x and y offsets based on the player's orientation and a
 * given offset value.
 *
 * This function sets the values pointed to by x_offset and y_offset according
 * to the specified orientation. The offset is applied in the direction
 * corresponding to the orientation:
 * - NORTH: x_offset is set to -offset, y_offset is unchanged.
 * - SOUTH: x_offset is set to offset, y_offset is unchanged.
 * - EAST: y_offset is set to offset, x_offset is unchanged.
 * - WEST: y_offset is set to -offset, x_offset is unchanged.
 *
 * @param orientation The orientation of the player (NORTH, SOUTH, EAST, or
 * WEST).
 * @param offset The magnitude of the offset to apply.
 * @param x_offset Pointer to a long long where the computed x offset will be
 * stored.
 * @param y_offset Pointer to a long long where the computed y offset will be
 * stored.
 */
static void compute_offsets(zap_srv_player_orientation_t orientation,
    long long offset, long long *x_offset, long long *y_offset)
{
    switch (orientation) {
        case NORTH:
            *x_offset = -offset;
            return;
        case SOUTH:
            *x_offset = offset;
            return;
        case EAST:
            *y_offset = offset;
            return;
        case WEST:
            *y_offset = -offset;
            return;
        default:
            break;
    }
}

/**
 * @brief Computes a new position on the map based on the current position,
 * player orientation, map size, and an offset.
 *
 * This function calculates the new position by applying the given offset
 * in the direction specified by the orientation. The map is considered
 * toroidal, so positions wrap around the edges.
 *
 * @param pos Pointer to the current position structure.
 * @param orientation The orientation of the player (direction to move).
 * @param map_size Pointer to the structure containing the map's dimensions.
 * @param offset The number of units to move from the current position.
 * @return zap_srv_pos_t The new computed position on the map.
 */
zap_srv_pos_t compute_position(zap_srv_pos_t *pos,
    zap_srv_player_orientation_t orientation, zap_srv_pos_t *map_size,
    size_t offset)
{
    long long new_x;
    long long new_y;
    long long x_offset = 0;
    long long y_offset = 0;

    if (offset == 0) {
        return *pos;
    }
    compute_offsets(orientation, (long long)offset, &x_offset, &y_offset);
    new_x = ((long long)pos->x + x_offset + (long long)map_size->x) %
        (long long)map_size->x;
    new_y = ((long long)pos->y + y_offset + (long long)map_size->y) %
        (long long)map_size->y;
    return (zap_srv_pos_t){(size_t)new_x, (size_t)new_y};
}

/**
 * @brief Computes the next position of an entity on the map based on its
 * current position, orientation, and the map size.
 *
 * This function is a wrapper around compute_position, advancing the position
 * by one step.
 *
 * @param pos Pointer to the current position structure.
 * @param orientation The orientation of the player/entity.
 * @param map_size Pointer to the structure containing the map's dimensions.
 * @return The new position after moving one step in the given orientation.
 */
zap_srv_pos_t compute_next_position(zap_srv_pos_t *pos,
    zap_srv_player_orientation_t orientation, zap_srv_pos_t *map_size)
{
    return compute_position(pos, orientation, map_size, 1);
}
