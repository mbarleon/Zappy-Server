/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions
*/

#ifndef ZAP_SRV_PLAYER_ACTIONS_INTERNAL_H_
    #define ZAP_SRV_PLAYER_ACTIONS_INTERNAL_H_
    #include "macro.h"
    #include <cextend/macro.h>
    #include "../player_functions.h"
    #include <cextend/snprintf_alloc.h>

void player_set(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_look(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_left(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_fork(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_take(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_eject(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_right(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_forward(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
void player_inventory(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);
void player_broadcast(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);
void player_connect_nbr(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);
void player_incantation(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);

#endif /* !ZAP_SRV_PLAYER_ACTIONS_INTERNAL_H_ */
