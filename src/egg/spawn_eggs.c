/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** spawn_eggs
*/

#include "egg_internal.h"

/**
 * @brief Returns the smaller of two size_t values.
 *
 * This function compares two size_t values and returns the minimum of the two.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 * @return The smaller of the two values.
 */
static size_t min(size_t a, size_t b)
{
    return a < b ? a : b;
}

/**
 * @brief Computes the target number of eggs to spawn per team based on the
 * map size and team count.
 *
 * This function calculates the optimal number of eggs that should be spawned
 * for each team. The calculation is based on the total map area
 * (width * height) divided by the number of teams, ensuring that the result
 * does not exceed the maximum allowed clients per team.
 *
 * @param ctxt Pointer to the parsed server context containing map dimensions,
 * team list, and max clients per team.
 * @return The target number of eggs to spawn per team.
 */
static size_t compute_target_eggs_per_team(
    const zap_srv_parsed_context_t *ctxt)
{
    const size_t map_size = ctxt->map.x * ctxt->map.y;
    size_t nteams = 0;

    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        nteams++;
    }
    return min((size_t)floor((double)map_size / (double)nteams),
        ctxt->max_clients_per_team);
}

/**
 * @brief Spawns eggs for each team on the map.
 *
 * This function calculates the number of eggs to spawn per team,
 * generates a shuffled list of positions on the map, and assigns
 * eggs to each team at those positions. Each team's available_slots
 * is set to the number of eggs spawned. The positions array is freed
 * after use.
 *
 * @param ctxt Pointer to the parsed server context containing map and team
 * information.
 */
void spawn_eggs(zap_srv_parsed_context_t *ctxt)
{
    const size_t eggs_per_team = compute_target_eggs_per_team(ctxt);
    size_t pos_idx = 0;
    zap_srv_pos_t *positions =
        generate_shuffled_positions(ctxt->map.x, ctxt->map.y);

    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        tmp->available_slots = eggs_per_team;
        for (size_t i = 0; i < eggs_per_team; ++i) {
            add_egg(&tmp->eggs, &positions[pos_idx], -1);
            pos_idx++;
        }
    }
    free(positions);
}
