/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** types
*/

#ifndef ZAP_SRV_TYPES_H_
    #define ZAP_SRV_TYPES_H_
    #include <stddef.h>

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

#endif /* !ZAP_SRV_TYPES_H_ */
