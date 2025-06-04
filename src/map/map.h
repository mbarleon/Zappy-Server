/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** map
*/

#ifndef ZAP_SRV_MAP_H_
    #define ZAP_SRV_MAP_H_
    #include <stddef.h>
    #include "../elements/elements.h"

/**
 * @struct zap_srv_map_t
 * @brief Represents a 2D map coordinate with x and y positions.
 *
 * This structure is used to store the coordinates (x, y) on the server map,
 * and the elements for each position.
 */
typedef struct {
    /**
     * @brief The x-coordinate of the map position.
     */
    size_t x;
    /**
     * @brief The y-coordinate of the map position.
     */
    size_t y;
    /**
     * @brief The elements in the map.
     */
    zap_srv_elements_list_t ***elements;
} zap_srv_map_t;

void generate_map(zap_srv_map_t *map);

#endif /* !ZAP_SRV_MAP_H_ */
