/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** density_table
*/

#include "elements.h"

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
const float density_table[] = {
    0.5F,
    0.3F,
    0.15F,
    0.1F,
    0.1F,
    0.08F,
    0.05F
};
