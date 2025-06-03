/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** density_table
*/

#include "map_internal.h"

/**
 * @brief Table defining the density values for each resource type on the map.
 *
 * This static constant array associates each resource type (such as FOOD,
 * LINEMATE, etc.)
 * with a floating-point density value, which determines the relative abundance
 * of each resource when generating the map in the Zappy server.
 *
 * Each entry in the table is of type zap_srv_dentity_table_t, containing:
 *   - The resource identifier (e.g., FOOD, LINEMATE)
 *   - The corresponding density as a float
 *
 * The sum of densities does not need to be 1.0, as each value represents the
 * relative
 * probability or frequency of the resource's appearance.
 */
const zap_srv_dentity_table_t density_table[] = {
    {FOOD, 0.5F},
    {LINEMATE, 0.3F},
    {DERAUMERE, 0.15F},
    {SIBUR, 0.1F},
    {MENDIANE, 0.1F},
    {PHIRAS, 0.08F},
    {THYSTAME, 0.05F}
};
