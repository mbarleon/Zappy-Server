/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** players
*/

#ifndef ZAP_SRV_PLAYERS_H_
    #define ZAP_SRV_PLAYERS_H_
    #include <time.h>
    #include "types.h"
    #include <stddef.h>
    #include <sys/types.h>
    #include "player_actions.h"
    #include "../elements/elements.h"
    #include "../server/zap_srv_socket.h"

    #define ZAP_SRV_MAX_ACTIONS 10

/**
 * @brief Structure representing an action performed by a player.
 *
 * This structure holds information about a player's action, including
 * the arguments associated with the action, the timestamp when the action
 * was performed, and the specific action type.
 *
 * @typedef zap_srv_actions_t
 */
typedef struct {
    /**
     * @brief Pointer to a string containing the action's arguments.
     */
    char *arguments;
    /**
     * @brief Time at which the action was performed.
     */
    time_t timestamp;
    /**
     * @brief The type of action performed by the player
     * (zap_srv_player_actions_t).
     */
    zap_srv_player_actions_t action;
} zap_srv_actions_t;

/**
 * @struct player_t
 * @brief Represents a player in the Zappy server.
 *
 * This structure holds all relevant information about a player,
 * including their team, position, socket, inventory, action timestamps,
 * and buffered actions.
 */
typedef struct {
    ssize_t id;
    /**
     * @brief The name of the team the player belongs to.
     */
    char *team;
    /**
     * @brief Buffer for the commands
     */
    char *buf;
    /**
     * @brief Length of the buffer.
     */
    size_t buf_size;
    /**
     * @brief The current position of the player on the map.
     */
    zap_srv_pos_t pos;
    /**
     * @brief The socket associated with the player for network communication.
     */
    zap_srv_socket_t sock;
    /**
     * @brief The inventory of the player, storing the quantity of each
     * element.
     */
    size_t inventory[ZAP_SRV_ELEMENTS_QUANTITY];
    /**
     * @brief Action buffer for the current player.
     */
    zap_srv_actions_t actions[ZAP_SRV_MAX_ACTIONS];
} zap_srv_player_t;

#endif /* !ZAP_SRV_PLAYERS_H_ */
