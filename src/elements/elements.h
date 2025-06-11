/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** elements
*/

#ifndef ZAP_SRV_ELEMENTS_H_
    #define ZAP_SRV_ELEMENTS_H_
    #define ZAP_SRV_ELEMENTS_QUANTITY 7

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
    UNKNOWN_ELEMENT = -1,
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

extern const float density_table[];
const char *get_elements_str(zap_srv_elements_t element);
zap_srv_elements_t get_element_from_str(const char *str);

#endif /* !ZAP_SRV_ELEMENTS_H_ */
