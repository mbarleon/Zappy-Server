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
    #include <stdbool.h>
    #include <sys/types.h>
    #include "player_actions.h"
    #include "../elements/elements.h"
    #include "../server/zap_srv_socket.h"

    #define ZAP_SRV_MAX_ACTIONS 10
    #define ZAP_SRV_FOOD_TIME_UNITS 126
    #define ZAP_SRV_BASE_TIME_UNITS 1260

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
    double timestamp;
    /**
     * @brief The type of action performed by the player
     * (zap_srv_player_actions_t).
     */
    zap_srv_player_actions_t action;
} zap_srv_actions_t;

typedef enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} zap_srv_player_orientation_t;

/**
 * @struct player_t
 * @brief Represents a player in the Zappy server.
 *
 * This structure holds all relevant information about a player,
 * including their team, position, socket, inventory, action timestamps,
 * and buffered actions.
 */
typedef struct {
    /**
     * @brief Is player participating to an incantation.
     */
    bool in_incentation;
    /**
     * @brief Is player dead.
     */
    bool dead;
    /**
     * @brief number of time units of the player.
     */
    double time_units;
    /**
     * @brief Player birth time.
     */
    double birth_time;
    /**
     * @brief ID of the player.
     */
    ssize_t id;
    /**
     * @brief Level of the player.
     */
    ssize_t level;
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
     * @brief The current orientation of the player.
     */
    zap_srv_player_orientation_t orientation;
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
