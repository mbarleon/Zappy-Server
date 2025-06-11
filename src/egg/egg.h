/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** egg
*/

#ifndef ZAP_SRV_EGG_H_
    #define ZAP_SRV_EGG_H_
    #include "types.h"
    #include <stddef.h>
    #include <sys/types.h>

/**
 * @brief Structure representing an egg in the Zappy server.
 *
 * This structure holds information about an egg, including its unique number,
 * position, the number of the player who laid it, and a pointer to the next
 * egg in a linked list.
 */
typedef struct zap_srv_egg_s {
    /**
     * @brief Unique identifier for the egg.
     */
    ssize_t number;
    /**
     * @brief Position of the egg on the map (zap_srv_pos_t).
     */
    zap_srv_pos_t pos;
    /**
     * @brief Identifier of the player who laid the egg.
     */
    ssize_t player_number;
    /**
     * @brief Pointer to the next egg in the linked list.
     */
    struct zap_srv_egg_s *next;
} zap_srv_egg_t;

#endif /* !ZAP_SRV_EGG_H_ */
