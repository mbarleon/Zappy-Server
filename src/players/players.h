/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** players
*/

#ifndef ZAP_SRV_PLAYERS_H_
    #define ZAP_SRV_PLAYERS_H_
    #include "types.h"
    #include <stddef.h>
    #include "../elements/elements.h"
    #include "../server/zap_srv_socket.h"

typedef struct {
    zap_srv_pos_t pos;
    zap_srv_socket_t sock;
    size_t inventory[ZAP_SRV_ELEMENTS_QUANTITY]
} player_t;

#endif /* !ZAP_SRV_PLAYERS_H_ */
