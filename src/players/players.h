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
     * @brief Timestamps for each action in the player's action buffer.
     */
    time_t actions_timestamp[ZAP_SRV_MAX_ACTIONS];
    /**
     * @brief Buffer holding the player's pending actions.
     */
    zap_srv_player_actions_t actions_buffer[ZAP_SRV_MAX_ACTIONS];
} zap_srv_player_t;

void player_actions(zap_srv_player_t *client);

#endif /* !ZAP_SRV_PLAYERS_H_ */
