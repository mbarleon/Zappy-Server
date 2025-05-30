/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** teams
*/

#ifndef ZAP_SRV_TEAM_H_
    #define ZAP_SRV_TEAM_H_
    #include <stddef.h>

typedef struct zap_srv_team_s {
    const char *name;
    size_t num_clients;
    size_t max_clients;
    struct zap_srv_team_s *next;
} zap_srv_team_t;

void create_team(zap_srv_team_t **teams, const char *str, size_t max_clients);

#endif /* !ZAP_SRV_TEAM_H_ */
