/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions
*/

#ifndef ZAP_SRV_PLAYER_ACTIONS_INTERNAL_H_
    #define ZAP_SRV_PLAYER_ACTIONS_INTERNAL_H_
    #include "macro.h"
    #include <stdbool.h>
    #include <cextend/macro.h>
    #include "../player_functions.h"
    #include <cextend/snprintf_alloc.h>
    #include "../../egg/egg_functions.h"

bool player_set(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_look(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_left(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_fork(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_take(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_eject(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_right(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_forward(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments);
bool player_inventory(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);
bool player_broadcast(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);
bool player_connect_nbr(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);
bool player_incantation(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, const char *arguments);

#endif /* !ZAP_SRV_PLAYER_ACTIONS_INTERNAL_H_ */
