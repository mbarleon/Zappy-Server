/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** generate_shuffled_positions
*/

#include "utils.h"

/**
 * @brief Generates an array of shuffled positions for a 2D map.
 *
 * This function creates an array of zap_srv_pos_t structures representing all
 * possible (x, y) positions on a map of size x by y. The positions are then
 * shuffled randomly using the Fisher-Yates algorithm.
 *
 * @param x The width of the map (number of columns).
 * @param y The height of the map (number of rows).
 * @return zap_srv_pos_t* Pointer to the dynamically allocated array of
 * shuffled positions,  or NULL if memory allocation fails. The caller is
 * responsible for freeing the memory.
 */
zap_srv_pos_t *generate_shuffled_positions(ssize_t x, ssize_t y)
{
    size_t offset;
    size_t idx = 0;
    zap_srv_pos_t tmp;
    ssize_t m_size = x * y;
    zap_srv_pos_t *positions = malloc(sizeof(zap_srv_pos_t) * (size_t)m_size);

    if (!positions)
        return NULL;
    for (ssize_t i = 0; i < x; ++i)
        for (ssize_t j = 0; j < y; ++j) {
            positions[idx] = (zap_srv_pos_t){i, j};
            idx++;
        }
    for (ssize_t i = m_size - 1; i > 0; --i) {
        offset = (size_t)((size_t)rand() % ((size_t)i + 1));
        tmp = positions[i];
        positions[i] = positions[offset];
        positions[offset] = tmp;
    }
    return positions;
}
