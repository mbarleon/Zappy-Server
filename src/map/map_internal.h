/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** map_internal
*/

#ifndef ZAP_SRV_MAP_INTERNAL_H_
    #define ZAP_SRV_MAP_INTERNAL_H_
    #include "map.h"
    #include <stdlib.h>
    #include <stdbool.h>
    #include <cextend/memory.h>

    #define ZAP_SRV_ELEMENTS_QUANTITY 7
/**
 * @brief Structure representing an entry in the density table for server
 * elements.
 *
 * This structure associates a specific element type with its corresponding
 * density value, which can be used for map generation or resource distribution
 * logic.
 *
 * @typedef zap_srv_dentity_table_t
 */
typedef struct zap_srv_dentity_table_s {
    /**
     * @brief The type of element (zap_srv_elements_t) represented in the
     * table.
     */
    zap_srv_elements_t element;
    /**
     * @brief The density value (float) associated with the element.
     */
    float density;
} zap_srv_dentity_table_t;

/**
 * @brief Represents a position on the map with x and y coordinates.
 *
 * This structure is used to store the coordinates of a position
 * on the Zappy server map.
 */
typedef struct {
    /**
     * @brief X coordinate of the position.
     */
    size_t x;
    /**
     * @brief Y coordinate of the position.
     */
    size_t y;
} zap_srv_pos_t;


extern const zap_srv_dentity_table_t density_table[];
zap_srv_dentity_table_t *compute_density(const zap_srv_map_t *map);

#endif /* !ZAP_SRV_MAP_INTERNAL_H_ */
