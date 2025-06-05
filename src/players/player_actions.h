/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** player_actions
*/

#ifndef ZAP_SRV_PLAYER_ACTIONS_H_
    #define ZAP_SRV_PLAYER_ACTIONS_H_
    #include <stddef.h>

/**
 * @enum zap_srv_player_actions_t
 * @brief Enumerates the possible actions a player can perform in the Zappy
 * server.
 *
 * This enumeration defines all the actions that a player entity can execute,
 * such as moving, interacting with the environment, and communicating with
 * other players.
 *
 * @var ZAP_SRV_PL_FORWARD      Move the player forward.
 * @var ZAP_SRV_PL_RIGHT        Turn the player to the right.
 * @var ZAP_SRV_PL_LEFT         Turn the player to the left.
 * @var ZAP_SRV_PL_LOOK         Make the player look around.
 * @var ZAP_SRV_PL_INVENTORY    Display the player's inventory.
 * @var ZAP_SRV_PL_BROADCAST    Broadcast a message to other players.
 * @var ZAP_SRV_PL_CONNECT_NBR  Get the number of available connections (eggs).
 * @var ZAP_SRV_PL_FORK         Fork a new player (egg).
 * @var ZAP_SRV_PL_EJECT        Eject other players from the current tile.
 * @var ZAP_SRV_PL_TAKE         Take an object from the ground.
 * @var ZAP_SRV_PL_SET          Set an object on the ground.
 * @var ZAP_SRV_PL_INCANTATION  Start an incantation (level up).
 */
typedef enum {
    ZAP_SRV_PL_NONE = -1,
    ZAP_SRV_PL_FORWARD,
    ZAP_SRV_PL_RIGHT,
    ZAP_SRV_PL_LEFT,
    ZAP_SRV_PL_LOOK,
    ZAP_SRV_PL_INVENTORY,
    ZAP_SRV_PL_BROADCAST,
    ZAP_SRV_PL_CONNECT_NBR,
    ZAP_SRV_PL_FORK,
    ZAP_SRV_PL_EJECT,
    ZAP_SRV_PL_TAKE,
    ZAP_SRV_PL_SET,
    ZAP_SRV_PL_INCANTATION
} zap_srv_player_actions_t;

extern const size_t action_time[];

#endif /* !ZAP_SRV_PLAYER_ACTIONS_H_ */
