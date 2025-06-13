/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** teams
*/

#ifndef ZAP_SRV_TEAM_H_
    #define ZAP_SRV_TEAM_H_
    #include <stddef.h>
    #include <stdbool.h>
    #include "../egg/egg.h"

/**
 * @struct zap_srv_team_s
 * @brief Represents a team in the Zappy server.
 *
 * This structure holds information about a team, including its name,
 * the current number of clients in the team, the maximum allowed clients,
 * and a pointer to the next team in a linked list.
 */
typedef struct zap_srv_team_s {
    /**
     * @brief Is team dead.
     */
    bool seg;
    /**
     * @brief The name of the team.
     */
    const char *name;
    /**
     * @brief The current number of clients in the team.
     */
    size_t num_clients;
    /**
     * @brief Available slots for the team.
     */
    size_t available_slots;
    /**
     * @brief The maximum number of clients allowed in the team.
     */
    size_t max_clients;
    /**
     * @brief Number of players with max elevation level.
     */
    size_t max_elevation_players;
    /**
     * @brief eggs of the team.
     */
    zap_srv_egg_t *eggs;
    /**
     * @brief Pointer to the next team in the linked list.
     */
    struct zap_srv_team_s *next;
} zap_srv_team_t;

void create_team(zap_srv_team_t **teams, const char *str, size_t max_clients);

#endif /* !ZAP_SRV_TEAM_H_ */
