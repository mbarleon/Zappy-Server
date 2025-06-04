/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** player_actions
*/

#ifndef ZAP_SRV_PLAYER_ACTIONS_H_
    #define ZAP_SRV_PLAYER_ACTIONS_H_
    #include <stddef.h>

typedef enum {
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
