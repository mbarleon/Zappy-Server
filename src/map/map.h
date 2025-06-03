/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** map
*/

#ifndef ZAP_SRV_MAP_H_
    #define ZAP_SRV_MAP_H_
    #include <stddef.h>

/**
 * @struct zap_srv_map_t
 * @brief Represents a 2D map coordinate with x and y positions.
 *
 * This structure is used to store the coordinates (x, y) on the server map.
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
} zap_srv_map_t;

#endif /* !ZAP_SRV_MAP_H_ */
