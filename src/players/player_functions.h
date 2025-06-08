/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** player_functions
*/

#ifndef ZAP_SRV_PLAYER_FUNCTIONS_H_
    #define ZAP_SRV_PLAYER_FUNCTIONS_H_
    #include "players.h"
    #include <string.h>
    #include <stdlib.h>
    #include <strings.h>
    #include <stdbool.h>
    #include <cextend/memory.h>
    #include "../server/server.h"
    #include "../graphical/graphical.h"
    #include "../parse_args/parse_args.h"

void parse_buf(zap_srv_player_t *player);
void player_actions(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    size_t i);

#endif /* !ZAP_SRV_PLAYER_FUNCTIONS_H_ */
