/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** teams
*/

#ifndef ZAP_SRV_TEAM_H_
    #define ZAP_SRV_TEAM_H_

typedef struct zap_srv_team_s {
    const char *name;
    size_t num_clients;
    size_t max_clients;
    struct zap_srv_team_s *next;
} zap_srv_team_t;

#endif /* !ZAP_SRV_TEAM_H_ */
