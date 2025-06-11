/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions
*/

#ifndef ZAP_SRV_GRAPH_ACTIONS_H_
    #define ZAP_SRV_GRAPH_ACTIONS_H_
    #include "macro.h"
    #include <errno.h>
    #include <limits.h>
    #include <cextend/macro.h>
    #include "../graphical_internal.h"

void graph_msz(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_bct(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_mct(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_tna(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_ppo(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_plv(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_pin(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_sgt(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);
void graph_sst(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args);

int parse_graph_args(const char *args, zap_srv_graph_args_t *parsed,
    int cmd_idx, zap_srv_player_t *client);

size_t find_player_index(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, ssize_t id);

extern const char *authorized_strings[];

#endif /* !ZAP_SRV_GRAPH_ACTIONS_H_ */
