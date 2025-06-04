/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** compute_density
*/

#include "map_internal.h"

/**
 * @brief Initializes a zap_srv_dentity_table_t array with default values.
 *
 * This function sets each entry in the provided table to a specific entity
 * type (FOOD, LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME) with a
 * quantity of 0.0F.
 * The function does nothing if the provided table pointer is NULL.
 *
 * @param table Pointer to an array of zap_srv_dentity_table_t to initialize.
 */
static void create_null_table(float *table)
{
    if (!table) {
        return;
    }
    table[0] = 0.0F;
    table[1] = 0.0F;
    table[2] = 0.0F;
    table[3] = 0.0F;
    table[4] = 0.0F;
    table[5] = 0.0F;
    table[6] = 0.0F;
}

/**
 * @brief Counts the occurrences of each element type in a linked list and
 * updates their density in the table.
 *
 * Iterates through the given linked list of elements and increments the
 * density count for each element type in the provided density table.
 *
 * @param element Pointer to the head of the linked list of elements.
 * @param table Pointer to the density table where the count for each element
 * type will be incremented.
 */
static void count_element_types(const zap_srv_elements_list_t *element,
    float *table)
{
    for (const zap_srv_elements_list_t *tmp = element; tmp; tmp = tmp->next) {
        table[tmp->element] += 1.0F;
    }
}

/**
 * @brief Computes the density table of elements on the map.
 *
 * This function allocates and initializes a density table for all element
 * types defined by ZAP_SRV_ELEMENTS_QUANTITY. It iterates over the map's
 * elements, counting the occurrences of each element type and then normalizes
 * these counts by dividing by the total map size to obtain densities.
 *
 * @param map Pointer to the zap_srv_map_t structure representing the map.
 * @return Pointer to a newly allocated zap_srv_dentity_table_t array
 * containing the density of each element type, or NULL on allocation failure
 * or if the map size is zero.
 */
float *compute_density(const zap_srv_map_t *map)
{
    const size_t map_size = map->x * map->y;
    float *table = (float *)malloc(sizeof(float) * ZAP_SRV_ELEMENTS_QUANTITY);

    if (!table || map_size == 0) {
        return NULL;
    }
    create_null_table(table);
    if (!map->elements) {
        return table;
    }
    for (size_t i = 0; i < map->x; ++i) {
        for (size_t j = 0; j < map->y; ++j) {
            count_element_types(map->elements[i][j], table);
        }
    }
    for (size_t i = 0; i < ZAP_SRV_ELEMENTS_QUANTITY; ++i) {
        table[i] /= (float)map_size;
    }
    return table;
}
