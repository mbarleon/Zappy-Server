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
 * @enum zap_srv_elements_t
 * @brief Enumerates the different types of elements that can exist on the
 * Zappy server map.
 *
 * The elements include:
 * - FOOD: Represents food items.
 * - LINEMATE: Represents the linemate resource.
 * - DERAUMERE: Represents the deraumere resource.
 * - SIBUR: Represents the sibur resource.
 * - MENDIANE: Represents the mendiane resource.
 * - PHIRAS: Represents the phiras resource.
 * - THYSTAME: Represents the thystame resource.
 */
typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} zap_srv_elements_t;

/**
 * @struct zap_srv_elements_list_s
 * @brief Linked list node structure for storing elements on the Zappy server
 * map.
 *
 * This structure contains an element type and a pointer to the next node in
 * the list.
 */
typedef struct zap_srv_elements_list_s {
    /**
     * @brief The type of element stored in this node.
     */
    zap_srv_elements_t element;
    /**
     * @brief Pointer to the next element in the list.
     */
    struct zap_srv_elements_list_s *next;
} zap_srv_elements_list_t;

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
