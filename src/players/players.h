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
    #include "player_actions.h"
    #include "../elements/elements.h"
    #include "../server/zap_srv_socket.h"

    #define ZAP_SRV_MAX_ACTIONS 10

typedef struct {
    char *team;
    zap_srv_pos_t pos;
    zap_srv_socket_t sock;
    size_t inventory[ZAP_SRV_ELEMENTS_QUANTITY];
    time_t actions_timestamp[ZAP_SRV_MAX_ACTIONS];
    zap_srv_player_actions_t actions_buffer[ZAP_SRV_MAX_ACTIONS];
} player_t;

#endif /* !ZAP_SRV_PLAYERS_H_ */
