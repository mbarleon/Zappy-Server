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
    #include "../server/zap_srv_t.h"

/**
 * @brief Structure holding the parsed context for the Zappy server.
 *
 * This structure contains all the necessary information parsed from the server
 * arguments, including the server configuration, map details, team
 * information, and the maximum number of clients allowed per team.
 *
 * @typedef zap_srv_parsed_context_t
 */
typedef struct {
    /**
     * @brief The main server configuration and state.
     */
    zap_srv_t server;
    /**
     * @brief The map configuration and state.
     */
    zap_srv_map_t map;
    /**
     * @brief Pointer to an array of team structures.
     */
    zap_srv_team_t *teams;
    /**
     * @brief Maximum number of clients allowed per team.
     */
    size_t max_clients_per_team;
} zap_srv_parsed_context_t;

void parse_args(int ac, const char **av, zap_srv_parsed_context_t *ctxt);

#endif /* !ZAP_SRV_PARSE_ARGS_H_ */
