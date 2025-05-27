/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** parse_args
*/

#ifndef ZAP_SRV_PARSE_ARGS_H_
    #define ZAP_SRV_PARSE_ARGS_H_
    #include "../map/map.h"
    #include "../teams/teams.h"
    #include "../server/server.h"

typedef struct {
    zap_srv_t server;
    zap_srv_map_t map;
    zap_srv_team_t *teams;
    size_t max_clients_per_team;
} zap_srv_parsed_context_t;

void parse_args(int ac, const char **av, zap_srv_parsed_context_t *ctxt);

#endif /* !ZAP_SRV_PARSE_ARGS_H_ */
